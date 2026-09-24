#!/usr/bin/env bash
# corrige.sh — confere os exercícios da Escada da P1 (AED I)
#
# Uso (dentro da pasta p1):
#   ./corrige.sh 5          compila ex5.c e roda os testes de testes/ex5
#   ./corrige.sh ex5.c      o mesmo (aceita também um caminho completo)
#   ./corrige.sh            corrige todos os exN.c que existirem na pasta
#
# Variáveis opcionais:
#   CC=gcc ./corrige.sh 5   escolhe o compilador (padrão: clang, se existir; senão gcc)
#   SAN=0  ./corrige.sh 5   desliga os sanitizers (AddressSanitizer e UBSan)
#   TEMPO=5 ./corrige.sh 5  segundos por teste antes de acusar laço infinito (padrão: 2)
#   TUDO=1 ./corrige.sh 5   mostra a tabela linha a linha mesmo nos testes que passaram

set -u
DIR="$(cd "$(dirname "$0")" && pwd)"
TESTES="$DIR/testes"
TEMPO="${TEMPO:-2}"
SAN="${SAN:-1}"
TUDO="${TUDO:-0}"
LARG=34

if [ -z "${CC:-}" ]; then
    if command -v clang >/dev/null 2>&1; then CC=clang; else CC=gcc; fi
fi
FLAGS=(-std=c99 -Wall -Wextra -g)
if [ "$SAN" = 1 ]; then
    if printf 'int main(void){return 0;}\n' | "$CC" -x c - -fsanitize=address,undefined -o /dev/null >/dev/null 2>&1; then
        FLAGS+=(-fsanitize=address,undefined -fno-omit-frame-pointer)
    else
        echo "(aviso: $CC não tem sanitizers aqui; seguindo sem eles)"
        SAN=0
    fi
fi
if command -v timeout >/dev/null 2>&1; then TO=(timeout "$TEMPO")
elif command -v gtimeout >/dev/null 2>&1; then TO=(gtimeout "$TEMPO")
else TO=(); fi

ASAN_OPTIONS="abort_on_error=0"
[ "$(uname)" = Linux ] && ASAN_OPTIONS="$ASAN_OPTIONS:detect_leaks=1"
export ASAN_OPTIONS
export LSAN_OPTIONS="exitcode=0"     # vazamento só avisa: não corta a saída do programa
export UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=1"

# Tira \r (arquivos do Windows), espaços no fim das linhas e linhas vazias no final.
normaliza() {
    tr -d '\r' < "$1" | sed 's/[[:space:]]*$//' |
        awk '{ l[NR] = $0 } END { n = NR; while (n > 0 && l[n] == "") n--; for (i = 1; i <= n; i++) print l[i] }'
}

corta() {
    local s="$1"
    if [ "${#s}" -le "$LARG" ]; then printf "%s" "$s"; else printf "%s..." "${s:0:$((LARG - 3))}"; fi
}

# compara ESPERADO OBTIDO ROTULO -> 0 se igual; imprime a tabela quando difere (ou se TUDO=1)
compara() {
    local esp="$1" obt="$2" rot="$3" i max e o st igual=1
    local -a E O
    mapfile -t E < <(normaliza "$esp")
    if [ ! -f "$obt" ]; then
        echo "      $rot: o arquivo não foi criado"
        return 1
    fi
    mapfile -t O < <(normaliza "$obt")
    max=${#E[@]}; [ ${#O[@]} -gt "$max" ] && max=${#O[@]}
    for ((i = 0; i < max; i++)); do
        [ "${E[i]-}" != "${O[i]-}" ] && igual=0
    done
    if [ "$igual" = 1 ] && [ "$TUDO" != 1 ]; then return 0; fi
    echo "      $rot:"
    printf "      | %5s | %-${LARG}s | %-${LARG}s | %-6s |\n" "LINHA" "ESPERADO" "OBTIDO" "STATUS"
    for ((i = 0; i < max; i++)); do
        e="${E[i]-}"; o="${O[i]-}"
        if [ "$e" = "$o" ]; then st="ok"; else st="ERRO"; fi
        printf "      | %5d | %-${LARG}s | %-${LARG}s | %-6s |\n" "$((i + 1))" "$(corta "$e")" "$(corta "$o")" "$st"
    done
    [ "$igual" = 1 ]
}

corrige_um() {
    local n="$1" src="$2" pasta="$TESTES/ex$1" exe t tmp st ok nota total=0 passou=0 f
    if [ ! -d "$pasta" ]; then
        echo "ex$n: não há testes para este degrau (rastreio e conversão se conferem pela página)."
        return 2
    fi
    if [ ! -f "$src" ]; then echo "ex$n: não achei $src"; return 2; fi
    exe="$(mktemp)"
    echo "== ex$n.c"
    if ! "$CC" "${FLAGS[@]}" "$src" -o "$exe" -lm 2> "$exe.cc"; then
        echo "   ERRO DE COMPILAÇÃO:"
        grep -E "error|erro" "$exe.cc" | head -10 | sed 's/^/   /'
        rm -f "$exe" "$exe.cc"
        RESUMO+=("ex$n: não compilou")
        return 1
    fi
    if grep -q "warning" "$exe.cc"; then
        echo "   Avisos do compilador (costumam ser bug):"
        grep "warning" "$exe.cc" | head -5 | sed 's/^/   /'
    fi

    for t in $(ls "$pasta" | sort -n); do
        total=$((total + 1))
        tmp="$(mktemp -d)"
        [ -d "$pasta/$t/arquivos" ] && cp -R "$pasta/$t/arquivos/." "$tmp/"
        ( cd "$tmp" && "${TO[@]}" "$exe" < "$pasta/$t/entrada.txt" > "$tmp/.saida" 2> "$tmp/.erro" )
        st=$?
        ok=1; nota=""
        if [ "$st" -eq 124 ]; then
            ok=0; nota="passou de ${TEMPO}s: laço infinito ou scanf esperando algo que não vem"
        elif grep -q "ERROR: AddressSanitizer" "$tmp/.erro"; then
            ok=0; nota="erro de memória: $(grep -m1 -oE 'AddressSanitizer: [a-z-]+' "$tmp/.erro" | cut -d' ' -f2)"
        elif grep -q "runtime error" "$tmp/.erro"; then
            ok=0; nota="comportamento indefinido: $(grep -m1 -oE 'runtime error: .*' "$tmp/.erro" | cut -c16-80)"
        elif [ "$st" -ge 128 ]; then
            ok=0; nota="o programa quebrou (sinal $((st - 128)))"
        elif grep -q "LeakSanitizer" "$tmp/.erro"; then
            nota="vazou memória: faltou free"
        fi

        if [ "$ok" = 0 ] && [ ! -s "$tmp/.saida" ]; then
            echo "      (sem saída na tela: o programa parou antes de imprimir ou a saída se perdeu no erro)" > "$tmp/.tab"
        elif ! compara "$pasta/$t/saida.txt" "$tmp/.saida" "saída na tela" > "$tmp/.tab"; then ok=0; fi
        if [ -d "$pasta/$t/esperado" ]; then
            for f in "$pasta/$t/esperado"/*; do
                compara "$f" "$tmp/$(basename "$f")" "arquivo $(basename "$f")" >> "$tmp/.tab" || ok=0
            done
        fi

        if [ "$ok" = 1 ]; then
            passou=$((passou + 1))
            echo "   [ok]     teste $t${nota:+  (atenção: $nota)}"
        else
            echo "   [FALHOU] teste $t${nota:+  ($nota)}"
        fi
        cat "$tmp/.tab"
        if [ -n "$nota" ] && grep -qE "ex[0-9]+\.c:[0-9]+" "$tmp/.erro"; then
            echo "      onde: $(grep -oE "ex[0-9]+\.c:[0-9]+" "$tmp/.erro" | head -3 | tr '\n' ' ')"
        fi
        rm -rf "$tmp"
    done
    rm -f "$exe" "$exe.cc"
    echo "   $passou de $total testes passaram"
    RESUMO+=("ex$n: $passou/$total")
    [ "$passou" = "$total" ]
}

RESUMO=()
falhou=0
if [ $# -eq 0 ]; then
    achou=0
    for src in $(ls "$DIR"/ex*.c 2>/dev/null | sort -V); do
        n="$(basename "$src" | grep -oE '[0-9]+' | head -1)"
        [ -d "$TESTES/ex$n" ] || continue
        achou=1
        corrige_um "$n" "$src" || falhou=1
        echo
    done
    [ "$achou" = 0 ] && { echo "Nenhum exN.c com testes em $DIR"; exit 2; }
else
    for arg in "$@"; do
        n="$(basename "$arg" | grep -oE '[0-9]+' | head -1)"
        [ -z "$n" ] && { echo "Não entendi '$arg'. Use: ./corrige.sh 5  ou  ./corrige.sh ex5.c"; exit 2; }
        if [ -f "$arg" ]; then src="$arg"; else src="$DIR/ex$n.c"; fi
        corrige_um "$n" "$src" || falhou=1
        echo
    done
fi
if [ ${#RESUMO[@]} -gt 1 ]; then
    echo "Resumo: ${RESUMO[*]}"
fi
exit "$falhou"
