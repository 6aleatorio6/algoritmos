#!/bin/bash
set -e

SRC="$1"
OUT="/tmp/programaPaia.o"

rm -f "$OUT" > /dev/null 2>&1
clang -std=c99 -O2 -lm "${SRC}/code.c" -o "$OUT"

set +e

# Itera sobre todos os arquivos input*
for IN_FILE in "${SRC}"/input*; do
    [ ! -f "$IN_FILE" ] && continue

    # Define o arquivo de resultado correspondente
    BASE=$(basename "$IN_FILE")
    RES_FILE="${SRC}/result${BASE#input}"

    [ ! -f "$RES_FILE" ] && continue

    mapfile -t OUT_LINES < <("$OUT" < "$IN_FILE")
    mapfile -t EXP_LINES < "$RES_FILE"

    echo ""
    echo "=================== Comparando $IN_FILE ========================================"
    printf "| %5s | %-50s | %-50s | %-8s |\n" "LINHA" "ESPERADO" "SAÍDA" "STATUS"
    echo "====================================================================================================="

    max=${#OUT_LINES[@]}
    [ ${#EXP_LINES[@]} -gt $max ] && max=${#EXP_LINES[@]}

    truncate() {
        local s="$1"
        local n="${2:-50}"
        [ "${#s}" -le "$n" ] && printf "%s" "$s" || printf "%s..." "${s:0:((n-3))}"
    }

    for ((i=0; i<max; i++)); do
        e="${EXP_LINES[i]:-}"
        o="${OUT_LINES[i]:-}"

        st="FAILED"
        [ "$o" = "$e" ] && st="PASS"

        printf "| %5d | %-50s | %-50s | %-8s |\n" \
            "$((i+1))" "$(truncate "$e")" "$(truncate "$o")" "$st"
    done

    echo "====================================================================================================="
    echo ""
done

rm -f "$OUT" > /dev/null 2>&1
