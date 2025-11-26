# Análisis de tablas de dispersión

* *Pablo Rodríguez Gniadek*
* *Marco Díaz Vera*

## Tamaño de tabla: xx
| Función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| Hash    |       4621(38)       |          19          |      0.65       |        1.39607         |
| Hash2   |      1803 (12)       |          12          |      0.65       |        0.544713        |
| Hash3   |      2535 (13)       |          12           |      0.65       |        0.765861        |

## Tamaño de tabla: yy
| Función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| Hash    |      4526 (43)       |          36          |      0.68       |        1.36737         |
| Hash2   |      1965 (13)       |          11          |      0.68       |        0.593656        |
| Hash3   |      2750 (14)       |          14          |      0.68       |        0.83016         |

## Justificación de la configuración elegida
Hemos optado por la configuración donde el factor de carga es 0.65 y
utilizando la segunda funcion hash, ya que es la que menos colisiones tiene,
diferenciando esta funcion de la tercera en este aspecto.


## Comparación de tiempos dados en milisegundos
Tiempo en realizar las búsquedas en la Tabla Hash:1 ms
Tiempo en realizar las búsquedas en la Lista:66 ms