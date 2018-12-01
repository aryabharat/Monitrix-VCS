output="$( bash <<EOF 
pwd
EOF
)"
output+="/monitrix"
#echo $output
sudo cp -r "$output" "/bin"
