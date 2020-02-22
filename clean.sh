for d in *; do
    if [ -d "$d" ]; then 
        echo $d
        cd $d
        make clean
        cd ..
    fi 
done
