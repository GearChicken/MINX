#!/bin/sh
# MINX configure script

#returns whether or not a debian package is installed
debInst()
{
  dpkg-query -Wf'${db:Status-abbrev}' "${1}" 2>/dev/null | grep -q '^i'
}

#checks if a debian package is installed, if not exit the script
checkInst()
{
  if debInst "${1}"; then
    echo "${1} is already installed!"
  else
    echo "${1} must be installed in order to build MINX!";
    exit 1;
  fi
}


#For now dpkg is required
command -v dpkg >/dev/null 2>&1 || { echo >&2 "I require dpkg but it's not installed.  Aborting."; exit 1; }
echo "dpkg is installed! Continuing Installation!\n"

#Read deps.lst line by line to check if proper dependencies are installed
while read line; do
  checkInst $line
done < deps.lst

echo "LGTM - You *Should* be able to build MINX!"
