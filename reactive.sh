instances=(50_50_3 50_250_3 100_250_3 100_500_3 150_150_3 250_750_3 300_500_3 300_2000_3 500_500_0 500_500_3)
for i in "${instances[@]}";
do
    title=$"INSTANCIA ${i}\n\n"
    result_file="reactive_${i}"
    full_file="results/"$result_file".txt"
    printf "$title" > "$full_file"
    for e in {1..10};
    do 
        subtitle=$"EXECUCAO ${e}\n"
        printf "$subtitle" >> "$full_file"
        ./execGrupo11 src/Problem.dat_${i} results/output.txt 3 2500 250 5 0.05 0.10 0.15 0.30 0.50
        cat ./results/output.txt >> "$full_file"
        printf "\n" >> "$full_file"
    done
    printf "=====\n\n" >> "$full_file"
done
