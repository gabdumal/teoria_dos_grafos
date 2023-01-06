instances=(50_50_3 50_250_3 100_250_3 100_500_3 150_150_3 250_750_3 300_500_3 300_2000_3 500_500_0 500_500_3)
for i in "${instances[@]}";
do
    title=$"INSTANCIA ${i}\n\n"
    result_file="greedy_${i}"
    full_file="results/"$result_file".txt"
    printf "$title" > "$full_file"
    ./execGrupo11 src/Problem.dat_${i} results/output.txt 1
    cat ./results/output.txt >> "$full_file"
    printf "=====\n\n" >> "$full_file"
done
