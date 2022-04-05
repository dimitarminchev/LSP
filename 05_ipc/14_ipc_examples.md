## Упражнение върху комуникация между процеси
Упражнете материалите от темата, като реализирате представените по-долу проекти.

### ReverseEncryptorDecryptor

Нека дефинираме "Reverse Encryption" (**RE**) като техника за защита на текстови съобщения, при която текста на съобщенията се обръща наобратно, преди те да бъдат изпратени по-нататък. Напишете програма **"revendec.c"**, която има два процеса, комуникиращи посредством анонимна тръба (**anonymous pipe**). 

За двата процеса да валидни следните правила:

- **Process 1** трябва да чете текст от клавиатурата, след това да приложи техниката RE и да изпрати кодираното съобщение на **Process 2**.
- **Process 2** трябва да изчака входящите съобщения, да отпечата кодираните съобщения на екрана, след това да ги декодира и да ги съхрани във файл **"messages.log"**.

### EncryptedChat

Напишете двойка програми за сървър и клиент (**"echatsrv.c"** and **"echatclnt.c"**). Сървърът трябва да имитира поведението на ***Process 1** от предишната задача, а клиента съответно на **Process 2**. Програмите трябва да използват наименувана тръба (**named pipe**) като метод за комуникация.