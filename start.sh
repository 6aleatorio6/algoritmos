#!/bin/bash
set -e

SRC="$1"
OUT="/tmp/programaPaia.o"

rm -f "$OUT" > /dev/null 2>&1
gcc "${SRC}/code.c" -o "$OUT"

set +e
 "$OUT" < "${SRC}/input.txt"
set -e


mapfile -t OUT_LINES < <("$OUT" < "${SRC}/input.txt")
mapfile -t EXP_LINES < "${SRC}/result.txt"

rm -f "$OUT" > /dev/null 2>&1

echo "====================================================================="
printf "| %5s | %-30s | %-30s | %-8s |\n" "LINHA" "ESPERADO" "SAÍDA" "STATUS"
echo "====================================================================="

max=${#OUT_LINES[@]}
[ ${#EXP_LINES[@]} -gt $max ] && max=${#EXP_LINES[@]}

truncate() {
    local s="$1"
    local n="${2:-30}"
    [ "${#s}" -le "$n" ] && printf "%s" "$s" || printf "%s..." "${s:0:((n-3))}"
}

for ((i=0; i<max; i++)); do
    e="${EXP_LINES[i]:-}"
    o="${OUT_LINES[i]:-}"

    st="FAILED"
    [ "$o" = "$e" ] && st="PASS"

    printf "| %5d | %-30s | %-30s | %-8s |\n" \
        "$((i+1))" "$(truncate "$e")" "$(truncate "$o")" "$st"
done

echo "====================================================================="
