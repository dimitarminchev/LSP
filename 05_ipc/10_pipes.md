## Анонимни и наименувани тръби

### Анонимни тръби

Анонимната тръба (_Термин на английски език: Anonymous pipe_) е обикновен **FIFO** комуникационен канал, който може да се използва за еднопосочна междупроцесна комуникация (IPC). Обикновено родителската програма отваря анонимни тръби и създава нов процес, който наследява другите краища на тръбите. Анонимната тръба трае само докато трае процесът.

### Наименувани тръби

Наименуваната тръба (_Термин на английски език: Named pipe_) е продължение на концепцията за традиционните анонимни тръби. Наименуваната тръба може да бъде идентифицирана с име и да се покаже като файл в системата. Наименуваната тръба може да продължи да съществува толкова дълго, колкото компютърната система е включена, а не само по време живота на процеса. Наименуваната тръба може да бъде изтрита, ако вече не се използва.
