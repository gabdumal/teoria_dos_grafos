alfas=(0.15 0.30 0.50)
instances=(50_50_3 50_250_3 100_250_3 100_500_3 150_150_3 250_750_3 300_500_3 300_2000_3 500_500_0 500_500_3)
for i in "${instances[@]}";
do
    title=$"INSTANCIA ${i}\n\n"
    result_file="randomized_${i}"
    full_file="results/"$result_file".txt"
    printf "$title" > "$full_file"
    for a in "${alfas[@]}";
    do
        subtitle=$"ALFA ${a} =============\n\n"
        printf "$subtitle" >> "$full_file"
        for e in {1..10};
        do 
            subsubtitle=$"EXECUCAO ${e}\n"
            printf "$subsubtitle" >> "$full_file"
            ./execGrupo11 src/Problem.dat_${i} results/output.txt 2 500 "${a}"
            cat ./results/output.txt >> "$full_file"
            printf "\n" >> "$full_file"
        done
        printf "=====\n\n" >> "$full_file"
    done
done
