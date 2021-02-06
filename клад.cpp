#include <iostream>

struct data
{
    int password;
    FILE* namefile;
    char name[54];

    char surname[50];
    char I[50];
    char o[50];
    char company[50];
    char index[50];
    char category[50];
    int  value;
    char arrival_data[50];
    char time[50];
    char exit_data[50];
    int size;
    void get()
    {
        printf("фамилия покупателя : %s\n", surname);
        printf("имя покупателя: %s \n", I);
        printf("Отчество покупателя: %s\n", o);
        printf("Фирма: %s \n", company);
        printf("индефикационный номер груза: %s\n", index);
        printf("Категория груза: %s \n", category);
        printf("ценность товара: %i рублей\n", value);
        printf("Дата поступления товара: %s\n", arrival_data);
        printf("срок аренды: %s \n", time);
        printf("Дата окончания аренды: %s\n", exit_data);
        printf("размер груза: %i кв.м.\n", size);

    }
    void fget()
    {
        fprintf(namefile, "%s ", surname);
        fprintf(namefile, "%s ", I);
        fprintf(namefile, "%s ", o);
        fprintf(namefile, "%s ", company);
        fprintf(namefile, "%s ", index);
        fprintf(namefile, "%s ", category);
        fprintf(namefile, "%i ", value);
        fprintf(namefile, "%s ", arrival_data);
        fprintf(namefile, "%s ", time);
        fprintf(namefile, "%s ", exit_data);
        fprintf(namefile, "%i", size);
    }
    void set()
    {
        printf("\nВведите данные о грузе и его владельце:\n");
        printf("введите фамилию:");
        scanf_s("%s", &surname, 50);
        printf("введите имя:");
        scanf_s("%s", &I, 50);
        printf("введите отчество:");
        scanf_s("%s", &o, 50);
        printf("введите имя организации:");
        scanf_s("%s", &company, 50);
        printf("введите индефикационный номер груза:(он должен быть уникальным для каждого товара, пример:'2w4e52f'):");
        scanf_s("%s", &index, 50);
        printf("введите категорию груза(пример:'рыба'):");
        scanf_s("%s", &category, 50);
        printf("введите ценность товара:(только число, в рублях, пример:'143'):");
        scanf_s("%i", &value);
        printf("введите дату поступления товара:(пример:'12.01.2020'):");
        scanf_s("%s", &arrival_data, 50);
        printf("введите срок аренды:(пример:'2дня' или  '3_месяца'):");
        scanf_s("%s", &time, 50);
        printf("введите дату окончания аренды:(пример:'12.02.2020'):");
        scanf_s("%s", &exit_data, 50);
        printf("укажите размер груза:(только число, в кв.м., пример:'123'):");
        scanf_s("%i", &size);
    }
    void fset()
    {
        fscanf_s(namefile, "%s", &surname, 50);
        fscanf_s(namefile, "%s", &I, 50);
        fscanf_s(namefile, "%s", &o, 50);
        fscanf_s(namefile, "%s", &company, 50);
        fscanf_s(namefile, "%s", &index, 50);
        fscanf_s(namefile, "%s", &category, 50);
        fscanf_s(namefile, "%i", &value);
        fscanf_s(namefile, "%s", &arrival_data, 50);
        fscanf_s(namefile, "%s", &time, 50);
        fscanf_s(namefile, "%s", &exit_data, 50);
        fscanf_s(namefile, "%i", &size);
    }

}pr;
void menufile(void);
int main();
void size_real()
{
    //pr.name имя склада 
    //size - со всеми расшиениями -- &name_storage
    //
    //
    char size[59] = "size_";
    printf("  %s:\t", pr.name);
    strcat_s(pr.name, ".txt");
    strcat_s(size, pr.name);
    int size_storage = 0;
    int size_real = 0;

    FILE* name_storage;
    fopen_s(&name_storage, size, "r");
    if (name_storage != NULL)
    {
        fscanf_s(name_storage, "%i", &size_storage);
        fclose(name_storage);

        fopen_s(&pr.namefile, pr.name, "r");
        while (fgetc(pr.namefile) != EOF)
        {
            pr.fset();
            size_real = size_real + pr.size;
        }
        printf(" занято %i из %i кв.м.\n\n", size_real, size_storage);
        fclose(pr.namefile);
        fclose(name_storage);
    }

}
void get_size()
{
    FILE* file;
    fopen_s(&file, "all_storage.txt", "r");
    printf("\n_________________________________________________________________\n\n\n");
    if (file == NULL)
        printf("Склады не обнаружены\n\n");
    else
    {
        while (fgetc(file) != EOF)
        {
            fscanf_s(file, "%s", &pr.name, 50);
            size_real();

        }
        fclose(file);

    }
    printf("_________________________________________________________________\n\n\n\n");
}
void delete_add()
{
    FILE* temp;
    int flag = 0;
    char number[50];
    printf("Введите имя склада:\n");
    scanf_s("%s", pr.name, 50);
    strcat_s(pr.name, ".txt");
    fopen_s(&pr.namefile, pr.name, "r");

    if (pr.namefile == NULL)
        printf("Склад с таким именем не обнаружен\n\n");
    else
    {
        fopen_s(&temp, "temp.txt", "w");
        printf("Введите индефикационный номер товара для удаления:");
        scanf_s("%s", &number, 50);
        while (fgetc(pr.namefile) != EOF)
        {
            pr.fset();
            if (strcmp(pr.index, number) != 0)
            {

                fprintf(temp, " %s ", pr.surname);
                fprintf(temp, "%s ", pr.I);
                fprintf(temp, "%s ", pr.o);
                fprintf(temp, "%s ", pr.company);
                fprintf(temp, "%s ", pr.index);
                fprintf(temp, "%s ", pr.category);
                fprintf(temp, "%i ", pr.value);
                fprintf(temp, "%s ", pr.arrival_data);
                fprintf(temp, "%s ", pr.time);
                fprintf(temp, "%s ", pr.exit_data);
                fprintf(temp, "%i", pr.size);
                flag++;
            }

        }
        if (flag == 0)
            printf("\n\nУдаление данного товара по данному номеру завершено!\n");
            
        else
            printf("\nПо данному индефикационному номеру товар не был обнаружен.\n\n");
        fclose(temp);
        fclose(pr.namefile);
        remove(pr.name);
        rename("temp.txt", pr.name);
    }
}
void read_data()

{
    printf("Введите имя склада:\n");
    scanf_s("%s", pr.name, 50);
    strcat_s(pr.name, ".txt");
    int num = 1;
    printf("\n_________________________________________________________________\n\n\n\n");
    fopen_s(&pr.namefile, pr.name, "r");
    if (pr.namefile == NULL)
    {
        printf("Склад с таким именем не обнаружен\n\n");
        printf("\n_________________________________________________________________\n\n\n\n");
    }
    else
    {
        while (fgetc(pr.namefile) != EOF)
        {
            printf("%i-ый товар\n", num);
            pr.fset();
            pr.get();
            printf("\n\n");
            num++;
        }
        if (num == 1)
            printf("На данный момент склад пуст\n\n");
        fclose(pr.namefile);
        printf("\n_________________________________________________________________\n\n");
    }

}
void add_data()
{
    printf("Введите имя склада:\n");
    scanf_s("%s", pr.name,50);
    strcat_s(pr.name, ".txt");
    fopen_s(&pr.namefile, pr.name, "r");
    if (pr.namefile == NULL)
        printf("Склад с таким именем не обнаружен\n\n");
    else
    {
        printf("\nВнимание! Все записи должны быть без пробелов!\n");
        fclose(pr.namefile);
        fopen_s(&pr.namefile, pr.name, "a");

        pr.set();
        fprintf(pr.namefile, " ");
        pr.fget();
        fclose(pr.namefile);
        printf("запись  прошла успешно!\n");
    }
}
void delete_storage()
{ // проверка и удаление файла склада с его размером
    int size_storage;
    char dublicate[50];
    FILE* name_storage;
    char size[59] = "size_";
    printf("Введите название склада, который хотите удалить:\n");
    scanf_s("%s", &pr.name,50);
    strcpy_s(dublicate, pr.name);
    strcat_s(pr.name, ".txt");
    fopen_s(&name_storage, pr.name, "r");
    if (name_storage == NULL)
        printf("Склад с таким именем не обнаружен\n\n");
    else
    {
        fclose(name_storage);
        remove(pr.name);
        strcat_s(size, pr.name);
        remove(size);

        //удаление из списка складов

        FILE* temp;
        int flag = 0;
        char name[50];
        fopen_s(&temp, "temp.txt", "w");
        fopen_s(&pr.namefile, "all_storage.txt", "r");
        {
            while (fgetc(pr.namefile) != EOF)
            {
                fscanf_s(pr.namefile, "%s", &name, 50);
                if (strcmp(dublicate, name) != 0)
                {

                    fprintf(temp, " %s", name);

                }

            }

            fclose(temp);
            fclose(pr.namefile);
            remove("all_storage.txt");
            rename("temp.txt", "all_storage.txt");
        }
        printf("\nУдаление произошло успешно!\n");
    }

}
int add_password()
{
    int password;
    FILE* name_password;
    fopen_s(&name_password, "password.txt", "w");
    printf("Введите новый пароль, \nВнимание!\n Он НЕ должен начинаться на 0 и должен состоять только из цифр, без пробелов\n");
    scanf_s("%i", &password);
    fprintf(name_password, "%i", password);
    fclose(name_password);
    return(password);
}
int pass()
{
    int password;
    FILE* name_password;
    fopen_s(&name_password, "password.txt", "r");
    if (name_password == NULL)
    {
        password = 0;
        return password;
    }
    else {
        fscanf_s(name_password, "%i", &password);
        fclose(name_password);
        return password;
    }

}
void create_storage()
{
    char size[59] = "size_";
    int size_storage;
    FILE* name_storage;
    printf("Внимание!! При написании имени уже существующего склада, все данные с него будут удалены! \nВ названии должны отсуствовать пробелы!\n");
    printf("Введите название склада:\n");
    scanf_s("%s", &pr.name, 54);

    fopen_s(&name_storage, "all_storage.txt", "a"); //ввод имени склада в файл
    fprintf(name_storage, " %s", pr.name);
    fclose(name_storage);

    strcat_s(pr.name, ".txt");
    fopen_s(&name_storage, pr.name, "w");
    fclose(name_storage);

    printf("\nВведите размер склада в кв.м, округлив до целого:\n");
    scanf_s("%i", &size_storage);
    strcat_s(size, pr.name);
    fopen_s(&name_storage, size, "w");
    fprintf(name_storage, "%i", size_storage);
    fclose(name_storage);
}
void settings()
{
    int op;
    while (true)
    {
        printf("\nВыберите, что нужно сделать: \n0:Выход в главное меню \n1:Редактирование\\Создание пароля \n2:Удаление пароля \n3:Создание нового склада\n4:Удаление склада\n");
        scanf_s("%i", &op);
        getchar();
        switch (op)
        {
        case 0:
            menufile();
            break;
        case 1:
            if (pr.password == 0)
            {
                pr.password = add_password();
            }
            else {
                printf("\nПотвердите пароль, чтобы продолжить действие\n");
                int ps;
                scanf_s("%i", &ps);
                if (ps == pr.password)
                {
                    pr.password = add_password();
                }
                else {
                    printf("Пароль введен неверно\n\n");
                }
            }
            break;
        case 2:
            printf("\nВы уверены, что хотите удалить пароль?\n0:Нет \n1:Да\n");
            scanf_s("%i", &op);
            if (op == 1)
            {
                if (pr.password == 0)
                {
                    printf("На данный момент пароль не установлен\n\n");
                }
                else {
                    printf("Потвердите пароль, чтобы продолжить удаление\n");
                    int ps;
                    scanf_s("%i", &ps);
                    if (ps == pr.password)
                    {
                        remove("password.txt");
                        printf("Пароль успешно удален! \n\n");
                        pr.password = pass();
                    }
                    else {
                        printf("Пароль введен неверно\n\n");
                    }
                }

            }
            break;
        case 3:
            create_storage();
            printf("\n склад успешно зарегистрирован!\n");
            break;
        case 4:
            printf("\nВы уверены, что хотите удалить склад? После этого все данные того склада будут потеряны\n0:Нет \n1:Да\n");
            scanf_s("%i", &op);
            if (op == 1)
            {
                if (pr.password == 0)
                {
                    delete_storage();
                }
                else {
                    printf("Потвердите пароль, чтобы продолжить удаление\n");
                    int ps;
                    scanf_s("%i", &ps);
                    if (ps == pr.password)
                    {
                        delete_storage();
                       
                    }
                    else {
                        printf("Пароль введен неверно\n\n");
                    }
                }

            }
            break;

        default:
            printf("данной команды не существует, доступные команды: 0,1,2,3,4\n");
            break;
        }
    }
}
void Search_menu()
{
    char search_word[50];
    int op;
    while (true)
    {
        int flag = 0;
        printf("\nПо какому критерию искать товар:\n0:Выход в меню \n1:Индефикационный номер  \n2:Фамилия \n3:Фирма \n");
        scanf_s("%i", &op);
        getchar();
        switch (op)
        {
        case 0:
            menufile();
            break;
        case 1:
            printf("Введите имя склада:\n");
            scanf_s("%s", pr.name, 50);
            strcat_s(pr.name, ".txt");
            fopen_s(&pr.namefile, pr.name, "r");
            if (pr.namefile == NULL)

                printf("Склад с таким именем не обнаружен\n\n");
            else
            {
                printf("Введите Индефикационный номер для поиска:");
                scanf_s("%s", &search_word, 50);

                printf("Товары, которые подошли по поиску:\n");
                printf("\n_________________________________________________________________\n\n\n\n");
                while (fgetc(pr.namefile) != EOF)
                {
                    pr.fset();
                    if (strcmp(pr.index, search_word) == 0)
                    {
                        pr.get();
                        printf("\n");
                        flag++;
                    }
                }
                if (flag == 0)
                    printf("\nПо данному индефикационному номеру товар не был обнаружен.\n\n");
                printf("\n_________________________________________________________________\n\n\n\n");
                fclose(pr.namefile);
                menufile();
            }
            break;
        case 2:
            printf("Введите имя склада:\n");
            scanf_s("%s", pr.name, 50);
            strcat_s(pr.name, ".txt");
            fopen_s(&pr.namefile, pr.name, "r");
            if (pr.namefile == NULL)

                printf("Склад с таким именем не обнаружен\n\n");
            else
            {
                printf("Введите фамилию для поиска:");
                scanf_s("%s", &search_word, 50);

                printf("Товары, которые подошли по поиску:\n");
                printf("\n_________________________________________________________________\n\n\n\n");
                while (fgetc(pr.namefile) != EOF)
                {
                    pr.fset();
                    if (strcmp(pr.surname, search_word) == 0)
                    {
                        pr.get();
                        printf("\n");
                        flag++;
                    }
                }
                if (flag == 0)
                    printf("\nПо данной фамилии товар не был обнаружен.\n\n");
                printf("\n_________________________________________________________________\n\n\n\n");
                fclose(pr.namefile);
                menufile();
            }
            break;
        case 3:
            printf("Введите имя склада:\n");
            scanf_s("%s", pr.name, 50);
            strcat_s(pr.name, ".txt");
            fopen_s(&pr.namefile, pr.name, "r");
            if (pr.namefile == NULL)

                printf("Склад с таким именем не обнаружен\n\n");
            else
            {
                printf("Введите фирму для поиска:");
                scanf_s("%s", &search_word, 50);

                printf("Товары, которые подошли по поиску:\n");
                printf("\n_________________________________________________________________\n\n\n\n");
                while (fgetc(pr.namefile) != EOF)
                {
                    pr.fset();
                    if (strcmp(pr.company, search_word) == 0)
                    {
                        pr.get();
                        printf("\n");
                        flag++;
                    }
                }
                if (flag == 0)
                    printf("\nПо данной фирме товар не был обнаружен.\n\n");
                printf("\n_________________________________________________________________\n\n\n\n");
                fclose(pr.namefile);
                menufile();
            }
            break;
        default:
            printf("данной команды не существует, доступные команды: 0,1,2,3\n");
            break;
        }
    }
}
void menufile(void)
{
    int op;
    while (true)
    {
        printf("\nвыберите, что нужно сделать: \n0:выйти из аккаунта и удалить историю работы \n1:добавить груз на склад \n2:удалить груз со склада \n3:просмотр всех грузов, имеющихся на складе \n4:найти определенный груз \n5:информация о загруженности складов\n6:настройки\n");
        scanf_s("%i", &op);
        getchar();
        switch (op)
        {
        case 0:
            main();
            break;
        case 1:

            add_data();
            break;
        case 2:
            delete_add();

            break;
        case 3:
            read_data();
            break;
        case 4:
            Search_menu();
            break;
        case 5:
            get_size();

            break;
        case 6:
            printf("\nВход в настройки\n");
            settings();
            break;

        default:
            printf("\nданной команды не существует, доступные команды: 0,1,2,3,4,5,6\n");
            break;
        }
    }
}
int main()
{
    pr.password = pass();
    system("title склад");
    system("chcp 1251&&cls");
    printf("Данная программа предназначена для сортировки и распределения различного товара на складе.\n");
    int op;
    while (true)
    {

        printf("\nВыберите, что нужно сделать: \n0:Выход из программы \n1:Активация программы \n");
        scanf_s("%i", &op);
        getchar();
        switch (op)
        {
        case 0:
            printf("\nБыл произведен выход из программы\n");
            exit(0);
            break;
        case 1:
            if (pr.password == 0)
            {
                printf("\nВнимание!\nНеобходимо поставить пароль и указать количество и размер складов в настройках для корректной работы программы.\n выполняется вход ... \n");
                menufile();
                break;
            }

            printf("Прежде чем начать пользоваться програмой, введите пароль администратора: \n");
            int ps;
            scanf_s("%i", &ps);
            if (ps == pr.password)
            {
                printf("Пароль введен верно! \n");
                menufile();
                break;
            }
            else
                printf("Неправильный пароль!\n");

        default:
            printf("Данной команды не существует, доступные команды: 0,1\n");
            break;
        }
    }
}
