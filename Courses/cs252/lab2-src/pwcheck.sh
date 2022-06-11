#!/bin/bash

#DO NOT REMOVE THE FOLLOWING TWO LINES
git add $0 >> .local.git.out
git commit -a -m "Lab 2 commit" >> .local.git.out
git push >> .local.git.out || echo


#Your code here

# if file path is given, extract to just filename
file="$(basename -- $1)"

# get word and its count in the file
WORD="$(head -n 1 $file)"
COUNT=${#WORD}

# if greater than 32 or less than 6, invalid and exit
if [ $COUNT -gt 32 ] || [ $COUNT -lt 6 ]
then
  echo "Error: Password length invalid."
  exit 1
fi

POINTS=$COUNT

# checks if there is a special character
if [[ $WORD =~ [#$\+%@] ]]
then
  POINTS=$((POINTS+5))
fi

# checks if there is a number
if [[ $WORD =~ [0-9] ]]
then
  POINTS=$((POINTS+5))
fi

# checks for an alpha character
if [[ $WORD =~ [A-Za-z] ]]
then
  POINTS=$((POINTS+5))
fi

# checks for a repeated alphanumeric
if  egrep -q '([0-9a-zA-Z])\1+' $file
then
  POINTS=$((POINTS-10))
fi

# checks for 3 or more consecutive lowercase
if  egrep -q '([a-z])([a-z])([a-z])' $file
then
  POINTS=$((POINTS-3))
fi

# checks for 3 or more consecutive uppercase
if  egrep -q '([A-Z])([A-Z])([A-Z])' $file
then
  POINTS=$((POINTS-3))
fi

# checks for 3 or more consecutive numbers
if  egrep -q '([0-9])([0-9])([0-9])' $file
then
  POINTS=$((POINTS-3))
fi

echo "Password Score: $POINTS"
exit 1