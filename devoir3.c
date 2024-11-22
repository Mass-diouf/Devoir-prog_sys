#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split_file(const char *file_name, int taille) 
{
    FILE *file = fopen(file_name, "rb");
    if (!file) 
    {
        perror("Erreur d douvertuure");
        return;
    }

    char buffer[1024];
    int part_num = 0;
    size_t read,written, left = taille;

    while ((read = fread(buffer, 1, left < sizeof(buffer) ? left : sizeof(buffer), file)) > 0) 
    {
        char part_name[256];
        snprintf(part_name, sizeof(part_name), "%s.part%d", file_name, part_num++);

        FILE *part_file = fopen(part_name, "wb");
        if (!part_file) 
        {
            perror("Error creating part file");
            fclose(file);
            return;
        }

        written = fwrite(buffer, 1, read, part_file);
        fclose(part_file);

        if (written < read) 
        {
            perror("Error ");
            fclose(file);
            return;
        }

        left -= read;
        if (left == 0) 
        {
           left = taille;
        }
    }

    fclose(file);
    printf("File split into %d parts.\n", part_num);
}
void join_files(const char *output_file, int num_parts, char *parts[]) 
{
    FILE *out_file = fopen(output_file, "wb");
    if (!out_file) 
    {
        perror("Error ");
        return;
    }

    char buffer[1024];
    for (int i = 0; i < num_parts; i++) 
    {
        FILE *part_file = fopen(parts[i], "rb");
        if (!part_file) 
        {
            perror("Error ");
            fclose(out_file);
            return;
        }

        size_t read;
        while ((read = fread(buffer, 1, sizeof(buffer), part_file)) > 0) 
        {
            size_t written = fwrite(buffer, 1, bytes_read, out_file);
            if (written < read) 
            {
                perror("Error ");
                fclose(part_file);
                fclose(out_file);
                return;
            }
        }

        fclose(part_file);
    }

    fclose(out_file);
    printf("Files joined into '%s'.\n", output_file);
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf(" ./split command arguments\n");
        printf("Commands:\n");
        printf("  split nomfichier taille\n");
        printf("  join nomfichier part1 part2 ...\n");
        return 1;
    }

    if (strcmp(argv[1], "split") == 0) {
        if (argc != 4) {
            printf("./split split file_name part_size\n");
            return 1;
        }

        const char *file_name = argv[2];
        int part_size = atoi(argv[3]);
        if (part_size <= 0) {
            printf("Error.\n");
            return 1;
        }

        split_file(file_name, part_size);
    } else if (strcmp(argv[1], "join") == 0) {
        if (argc < 4) 
        {
            printf(" ./split join output_file part1 part2 ...\n");
            return 1;
        }

        const char *output_file = argv[2];
        join_files(output_file, argc - 3, &argv[3]);
    } else {
        printf("Error: Unknown command '%s'.\n", argv[1]);
        return 1;
    }

    return 0;
}




