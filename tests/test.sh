#!/bin/sh

SECONDS=0
num_failed=0
num_passed=0

red=`tput setaf 1`
green=`tput setaf 2`
red_bg=`tput setab 1`
green_bg=`tput setab 2`
reset=`tput sgr0`
bold=`tput bold`

FAILED_TESTS=()

printf "${bold}=============================================\n"
printf "=========== FORMULA ONE TEST SUITE ==========\n"
printf "=============================================${reset}\n\n"

for file in maps/* ; do
    res=$(timeout 5s ./check $file)
    echo "$res" > results
    res=$(tail -1 results)

    printf "$file : "
    if [[ "$res" =~ 'Crash' ]] ; then
        printf "${bold}${red}crashed${reset}\n"
        ((num_failed++))
        FAILED_TESTS+=("$file")
    elif [[ "$res" =~ "finished" ]] ; then
        printf "${green}success${reset}\n"
        ((num_passed++))
    else
        printf "${red}${bold}fail (timeout)${reset}\n"
        FAILED_TESTS+=("$file")
        ((num_failed++))
    fi
done

rm results

printf "\n=============================================\n"
printf "================ TEST RESULTS ===============\n"
printf "=============================================\n"
num_tests=$((num_failed + num_passed))
printf "\n${bold}Total tests :${reset} $num_tests\n"
printf "${bold}Time to run :${reset} ${SECONDS}s\n"
printf "\n${bold}${green_bg} Passed : $num_passed/$num_tests ${reset} | ${bold}${red_bg} Failed : $num_failed/$num_tests ${reset}\n"

printf "\n=============================================\n"
printf "================ FAIL SUMMARY ===============\n"
printf "=============================================\n"

if [ ${#FAILED_TESTS[@]} ] ; then
echo "${red}${bold}Failed tests: ${reset}"
    for failed in ${FAILED_TESTS[@]} ; do
        echo "${red}$failed"
    done
fi
echo ${reset}

if [ "$num_failed" -eq 0 ] ; then
    printf "\n       ${bold}${green_bg} ALL TESTS SUCCESSFUL ${reset}\n"
fi
