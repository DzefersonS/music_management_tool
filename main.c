#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define START_UI 1
#define CRUD_UI 2

int song_entry_count = 0;

typedef struct
{
    char artist_name[50];
    char song_name[50];
    int song_length[3]; // indexes represent: 0 - hours, 1 - minutes, 2 - seconds
    int year;
} song_data;

void invalid_input();
void program_startup(song_data *songList);
void print_ui(int mode);
bool get_user_action(song_data *songList);
void get_new_song(song_data *songList);
void print_list(song_data *songList);
void edit_song(song_data *songList);
void remove_song(song_data *songList);
void exit_procedure(song_data *songList);
void load_bin_file(song_data *songList);

int main(void)
{
    song_data *songList = (song_data *)malloc(50 * sizeof(song_data));

    program_startup(songList);
    for (;;)
    {
        print_ui(CRUD_UI);
        if (get_user_action(songList) == false)
        {
            ;
        }
        else
        {
            break;
        }
    }

    return 0;
}

void print_ui(int mode)
{
    system("cls");
    switch (mode)
    {
    case START_UI:
        printf("Welcome to Totally Not Spotify! Since you just launched"
               " the program, would you like to load a bin file, or "
               " start with an empty file?\n");
        printf("-------------------------------------------------------\n");
        printf("1: Load bin file\n");
        printf("2: Start with empty file\n");
        break;
    case CRUD_UI:
        printf("What do you want to do, user?\n");
        printf("-------------------------------------------------------\n");
        printf("1: Enter a new song\n");
        printf("2: Edit a song\n");
        printf("3: Remove a song/songs\n");
        printf("4: View all songs\n");
        printf("5: Exit program\n");
        break;
    }
}

void program_startup(song_data *songList)
{
    char input_option;
    print_ui(START_UI);
    for (;;)
    {
        printf("Enter your option: ");
        input_option = getchar();
        if (getchar() != '\n')
        {
            invalid_input();
        }
        else if (input_option == '1')
        {
            load_bin_file(songList);
            return;
        }
        else if (input_option == '2')
        {
            printf("You have chosen to start with an empty file. Program will now continue!");
            return;
        }
        else
        {
            invalid_input();
        }
    }
}

bool get_user_action(song_data *songList)
{
    char input_option;
    for (;;)
    {
        printf("Enter your option: ");
        input_option = getchar();
        if (input_option < '1' || input_option > '5' || getchar() != '\n')
        {
            invalid_input();
        }
        else
        {
            switch (input_option)
            {
            case '1':
                if (song_entry_count == 50)
                {
                    printf("Can't enter more songs! Song count has reached 50, which is the limit.\n");
                    break;
                }
                else
                {
                    get_new_song(songList);
                    break;
                }

            case '2':
                edit_song(songList);
                break;
            case '3':
                remove_song(songList);
                break;
            case '4':
                print_list(songList);
                break;
            case '5':
                exit_procedure(songList);
                return true;
            }
        }

        return false;
    }
}

void get_new_song(song_data *songList)
{
    char temp;
    song_entry_count++;
    int index = song_entry_count - 1;
    system("cls");
    for (;;)
    {
        printf("Enter the name of the artist (max 50 characters): \n");
        scanf("%50[^\n]", songList[index].artist_name);
        if (getchar() != '\n')
        {
            while (getchar() != '\n')
                ;
        }
        if (songList[index].artist_name[0] == 0)
        {
            printf("Artist name cannot be empty.\n");
        }
        else
        {
            break;
        }
    }

    for (;;)
    {
        printf("Enter the name of the song (max 50 characters): \n");
        scanf("%50[^\n]", &songList[index].song_name);
        if (getchar() != '\n')
        {
            while (getchar() != '\n')
                ;
        }
        if (songList[index].song_name[0] == 0)
        {
            printf("Song name cannot be empty.\n");
        }
        else
        {
            break;
        }
    }

    for (;;)
    {
        int s, m, h;
        printf("Enter song length. Format: hh:mm:ss: ");
        if (scanf("%d:%d:%d", &songList[index].song_length[0], &songList[index].song_length[1], &songList[index].song_length[2]) == 3 && getchar() == '\n')
        {
            h = songList[index].song_length[0];
            m = songList[index].song_length[1];
            s = songList[index].song_length[2];
            if (m > 60 || s > 60)
            {
                printf("Invalid input! Check your entered times.\n");
                for (int i = 0; i < 3; ++i)
                {
                    songList[index].song_length[i] = 0;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            invalid_input();
        }
    }

    for (;;)
    {
        printf("Enter year of song release: ");
        int temp;
        if (scanf("%d", &temp) == 1 && getchar() == '\n')
        {
            if (temp <= 2022)
            {
                printf("%d %d", index, temp);
                songList[index].year = temp;
                break;
            }
            else
            {
                printf("Are you a time traveler? Try again.\n");
                temp = 0;
            }
        }
        else
        {
            invalid_input();
        }
    }

    return;
}

void print_list(song_data *songList)
{
    char temp;
    system("cls");
    for (int i = 0; i < song_entry_count; ++i)
    {
        printf("Song %d:\n", i + 1);
        printf("Artist: %s\n", songList[i].artist_name);
        printf("Song: %s\n", songList[i].song_name);
        printf("Song length: %d hours, %d minutes and %d seconds.\n", songList[i].song_length[0], songList[i].song_length[1], songList[i].song_length[2]);
        printf("Release year: %d\n\n", songList[i].year);
    }
    printf("Enter 0 once you're done looking at the list.\n");
    for (;;)
    {
        temp = getchar();
        if (temp == '0' && getchar() == '\n')
        {
            return;
        }
        else
        {
            printf("Invalid input. Enter 0 to go back to menu.\n");
            while (getchar() != '\n')
                ;
        }
    }
}

void edit_song(song_data *songList)
{
    system("cls");
    int index;
    char command;
    for (;;)
    {
        printf("Enter the index of the song you want to edit (if you want to go back to the menu, enter 0): ");
        if (scanf("%d", &index) == 1 && getchar() == '\n')
        {
            if (index == 0)
            {
                return;
            }
            else
            {
                printf("Selected song: %s by %s.\n", songList[index - 1].song_name, songList[index - 1].artist_name);
                index -= 1;
                for (;;)
                {
                    printf("Select what to edit. 1 - artist name, 2 - song name, 3 - song length, 4 - release year, 0 - go back to main menu.\n");
                    command = getchar();
                    if (getchar() != '\n' || command < '0' || command > '4')
                    {
                        invalid_input();
                    }
                    else
                    {
                        char temp[50];
                        if (command == '0')
                        {
                            return;
                        }
                        else if (command == '1')
                        {
                            for (;;)
                            {
                                printf("Enter the new name of the artist (max 50 characters): \n");
                                scanf("%50[^\n]", songList[index].artist_name);
                                if (getchar() != '\n')
                                {
                                    while (getchar() != '\n')
                                        ;
                                }
                                if (songList[index].artist_name[0] == 0)
                                {
                                    printf("Artist name cannot be empty.\n");
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else if (command == '2')
                        {
                            for (;;)
                            {
                                printf("Enter the new name of the song (max 50 characters): \n");
                                scanf("%50[^\n]", songList[index].song_name);
                                if (getchar() != '\n')
                                {
                                    while (getchar() != '\n')
                                        ;
                                }
                                if (songList[index].song_name[0] == 0)
                                {
                                    printf("Song name cannot be empty.\n");
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else if (command == '3')
                        {
                            for (;;)
                            {
                                int s, m, h;
                                printf("Enter new song length. Format: hh:mm:ss: ");
                                if (scanf("%d:%d:%d", &songList[index].song_length[0], &songList[index].song_length[1], &songList[index].song_length[2]) == 3 && getchar() == '\n')
                                {
                                    h = songList[index].song_length[0];
                                    m = songList[index].song_length[1];
                                    s = songList[index].song_length[2];
                                    if (m > 60 || s > 60)
                                    {
                                        printf("Invalid input! Check your entered times.\n");
                                        for (int i = 0; i < 3; ++i)
                                        {
                                            songList[index].song_length[i] = 0;
                                        }
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    invalid_input();
                                }
                            }
                        }
                        else
                        {
                            for (;;)
                            {
                                printf("Enter new year of song release: ");
                                int temp;
                                if (scanf("%d", &temp) == 1 && getchar() == '\n')
                                {
                                    if (temp <= 2022)
                                    {
                                        printf("%d %d", index, temp);
                                        songList[index].year = temp;
                                        break;
                                    }
                                    else
                                    {
                                        printf("Are you a time traveler? Try again.\n");
                                        temp = 0;
                                    }
                                }
                                else
                                {
                                    invalid_input();
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            invalid_input();
        }
    }
}

void invalid_input()
{
    printf("Invalid input. Try again.\n");
    while (getchar() != '\n')
        ;
    return;
}

void remove_song(song_data *songList)
{
    system("cls");
    int index;
    char command;
    for (;;)
    {
        printf("Enter the index of the song you want to remove (if you want to go back to the menu, enter 0. If you want to remove every song, enter -1): ");
        if (scanf("%d", &index) == 1 && getchar() == '\n')
        {
            if (index == 0)
            {
                return;
            }
            else
            {
                if (index == -1)
                {
                    printf("Are you sure you want to do this? This action is irreversible. Enter Y or N: ");
                }
                else
                {
                    printf("Are you sure you want to delete %s by %s? This action is irreversible. Enter Y or N: ", songList[index - 1].song_name, songList[index - 1].artist_name);
                }
                command = getchar();
                if (getchar() != '\n')
                {
                    invalid_input();
                }
                else
                {
                    if (command == 'N')
                        ;
                    else if (index == -1)
                    {
                        for (int i = 0; i < song_entry_count; ++i)
                        {
                            songList[i].artist_name[0] = '\0';
                            songList[i].song_name[0] = '\0';
                            songList[i].song_length[0] = 0;
                            songList[i].song_length[1] = 0;
                            songList[i].song_length[2] = 0;
                            songList[i].year = 0;
                        }
                        song_entry_count = 0;
                    }
                    else
                    {
                        index -= 1;
                        for (int i = index; i < song_entry_count - 1; ++i)
                        {
                            strcpy(songList[i].artist_name, songList[i + 1].artist_name);
                            strcpy(songList[i].song_name, songList[i + 1].song_name);
                            songList[i].song_length[0] = songList[i + 1].song_length[0];
                            songList[i].song_length[1] = songList[i + 1].song_length[1];
                            songList[i].song_length[2] = songList[i + 1].song_length[2];
                            songList[i].year = songList[i + 1].year;
                        }

                        song_entry_count -= 1;
                    }
                }
            }
            printf("Song(s) removed successfully.\n");
        }
        else
        {
            invalid_input();
        }
    }
}

void exit_procedure(song_data *songList)
{
    system("cls");
    FILE *filename_ptr;
    char temp[50];
    printf("Before the program exits, do you want to save your song list? Enter Y or N:");

    char command;

    for (;;)
    {
        command = getchar();
        if (getchar() != '\n')
        {
            invalid_input();
        }
        else
        {
            if (command == 'N' || command == 'n')
            {
                return;
            }
            else if (command == 'Y' || command == 'y')
            {
                printf("Enter filename of output file (max 50 characters):");
                scanf("%50[^\n]", temp);
                if (getchar() != '\n')
                {
                    while (getchar() != '\n')
                        ;
                }
                strcat(temp, ".bin");
                filename_ptr = fopen(temp, "w");
                fprintf(filename_ptr, "%d\n", song_entry_count);
                for (int i = 0; i < song_entry_count; ++i)
                {

                    fprintf(filename_ptr, "%s\n", songList[i].artist_name);
                    fprintf(filename_ptr, "%s\n", songList[i].song_name);
                    fprintf(filename_ptr, "%d::%d::%d\n", songList[i].song_length[0], songList[i].song_length[1], songList[i].song_length[2]);
                    fprintf(filename_ptr, "%d\n", songList[i].year);
                }

                fclose(filename_ptr);
            }
        }

        return;
    }
}

void load_bin_file(song_data *songList)
{
    system("cls");
    char temp[50];
    printf("Enter filename:\n");
    scanf("%50[^\n]", temp);
    if (getchar() != '\n')
    {
        while (getchar() != '\n')
            ;
    }

    FILE *fp = fopen(strcat(temp, ".bin"), "r");

    fscanf(fp, "%d", &song_entry_count);
    fgetc(fp);

    for (int i = 0; i < song_entry_count; ++i)
    {
        fscanf(fp, "%[^\n]", songList[i].artist_name);
        fgetc(fp);
        fscanf(fp, "%[^\n]", songList[i].song_name);
        fscanf(fp, "%d::%d::%d", &songList[i].song_length[0], &songList[i].song_length[1], &songList[i].song_length[2]);
        fscanf(fp, "%d", &songList[i].year);
        fgetc(fp);
    }
    return;
}