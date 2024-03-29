## Стандартни потоци

В общия случай, компютърните програми получават входна информация (_клавиатура, файл и т.н._), обработва я и извежда резултат, под формата на изходната информация (_файлове, текст, изображение и т.н._). За стандартните конзолни приложения, входните данни се въвеждат от клавиатурата на компютъра, а изходните данни се извеждат на текстов екран.

В този модел на вход и изход на данните, не е известно предварително колко и какви данни ще бъдат получени от потребителите и съответно изведени като резултат. Такъв тип вход и изход се наричат текстови **потоци** (_Термин на Английски език: streams_).

Всяка програма, която изпълняваме на командния ред в Линукс, е свързана автоматично към три потока от данни: 

| поток      | информация                                                                                 |
|------------|--------------------------------------------------------------------------------------------|
| STDIN (0)  | Стандартен вход (данни, подадени в програмата, по подразбиране от клавиатурата)            |
| STDOUT (1) | Стандартен изход (данни, отпечатани от програмата, по подразбиране към текстовия терминал) |
| STDERR (2) | Стандартна грешка (за съобщения за грешки, по подразбиране към текстовия терминал)         |
 
![11_streams.png](11_streams.png)   

 
