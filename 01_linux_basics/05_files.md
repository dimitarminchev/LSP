## Файлове, директории и файлови системи

**Файловете** (_Термин на Английски език: Files_) са базово понятие във всички популярни операционни системи. Това напълно се отнася и за ОС Линукс, която се характеризира с това, че в нея “всичко е файл” (“everything is a file”). Файловете се групират в **директории** (_Термин на Английски език: Folders_), които от своя страна могат да съдържат други под-директории и по този начин се създава дървовидна структура.

[Файловата система](https://github.com/fosscourse/wiki/wiki/Файлова_система_в_Линукс_-_структура_и_основни_понятия) е начина за структуриране и организация на данните в компютъра. Тя представлява служебна таблица записана на диска, която операционната система използва, за да получи достъп до файловете. Записите в таблицата се наричат **inode** и накратко могат да се определят като сериен номер на файла.

Основни команди за работа с файловата система под Линукс са представени в таблицата по-долу:

| Команда | Описание                                             |
| ------- | ---------------------------------------------------- |
| pwd     | Отпечава името на текущата директория                |
| ls      | Списък на съдържанието на директорията               |
| mkdir   | Създава директория                                   |
| cd      | Смяна на работната директория                        |
| rmdir   | Изтриване на директория                              |
| cp      | Копиране на файлове и директории                     |
| mv      | Преместване и/или преименуване на файлове            |
| rm      | Изтриване на файлове и/или директории                |
| ln      | Създава връзка между файлове                         |
| cat     | Конкатенира файлове и отпечатва на стандартния изход |
 