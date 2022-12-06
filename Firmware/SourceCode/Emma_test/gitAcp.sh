#!/bin/bash
### This is for lazzy shit like me to [git-add -> git-commit -> git push]


# Help shit
help() {
    sed -rn 's/^### ?//;T;p' "$0"
}

if [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]]; then
    help
    exit 1
fi


# Git add all
git add .

# Git commit
echo "Commit message:"
read
git commit -a -m "${REPLY}"

# Git push
while true; do
    read -p "Do you wish to git push? (\no)" yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) echo "No push, exit"; exit;;
        * )     echo "No push, exit"; exit;;
    esac
done
git push

