#!/bin/sh
# progress.sh <atual> <total> "<mensagem>"

current="$1"
total="$2"
msg="$3"

# largura da barra
width=60

# saneamento
[ -z "$total" ]   && total=1
[ "$total" -eq 0 ] && total=1
[ -z "$current" ] && current=0
[ "$current" -lt 0 ] && current=0

filled=$(( width * current / total ))
[ "$filled" -gt "$width" ] && filled=$width
empty=$(( width - filled ))

# strings com largura variável (portátil)
bar=$(printf '%*s' "$filled" '' | tr ' ' '#')
space=$(printf '%*s' "$empty"  '')

# imprime a barra [########............] + contador e mensagem
printf '\r\033[36m[%s%s]\033[0m (%d/%d) %s' "$bar" "$space" "$current" "$total" "$msg"

# ao terminar, quebra a linha
if [ "$current" -ge "$total" ]; then
  printf '\n'
fi

exit 0
