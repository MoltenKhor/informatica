if [ $# -eq 0 ]; then
    echo "nessun file .dat trovato"
    exit 0
fi
for f ; do
        sum=0
        std=0
        cnt=0
        values=()
        exec 3<$f
        while IFS=" " read -u 3 line; do
            read -r -a elem <<<$line
            sum=$(echo "scale=2; $sum+${elem[1]}" | bc -q)
            values[$cnt]=${elem[1]}
            ((cnt += 1))
        done
        exec 3<&-
        avg=$(echo "scale=2; $sum/$cnt" | bc -q)
        sum=0
        for((i=0;i<$cnt;i++)); do
            sum=$(echo "scale=2; $sum+(${values[$i]}-$avg)^2" | bc -q)
        done
        if [ $cnt -gt 1]; then
            std=$(echo "scale=2; sqrt($sum/($cnt-1))" | bc -q)
        fi
        f1=${f%.???}
        f2=${f1##*/}
        echo "$f2 $cnt $avg $std" | awk '{printf "%-12s %-3d %8.2f %6.2f\n", $1, $2, $3, $4}'
    done    