#!/bin/bash

bold=$(tput bold)
normal=$(tput sgr0)
RED='\e[31m'
NC='\e[39m'

projectsWithNorm="ft_ping Libft get_next_line ft_printf puhs_swap so_long FdF fract-ol pipex minitalk minishell Philosophers minirt cub3d"

if [[ " $projectsWithNorm " =~ .*\ ${1}\ .* ]]; then
    echo "${1} has to be norm checked"
fi
nm ./${1} | grep U | tr -s ' ' | cut -d " " -f3 | cut -d "@" -f1 | grep -v ^_ > used_functions
grep -Fwvf ping_authorized_functions used_functions > forbidden_used

forbidden=0
while read p; do
  echo -e "${bold}${RED}forbidden functions used:${normal}${NC} $p"
done <forbidden_used