# Análisis de tablas de dispersión

* *Pablo Rodríguez Gniadek*
* *Marco Díaz Vera*

## Tamaño de tabla: xx
| Función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| Hash    |         4621         |          19          |      0.65       |           1            |
| Hash2   |         1803         |          12          |      0.65       |           0            |
| Hash3   |         2535         |          12           |      0.65       |           0            |

## Tamaño de tabla: yy
| Función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| Hash    |         4526         |          36          |      0.68       |           1            |
| Hash2   |         1965         |          11          |      0.68       |           0            |
| Hash3   |         2750         |          14          |      0.68       |           0            |

## Justificación de la configuración elegida
Hemos optado por la configuración donde el factor de carga es 0.65 y
utilizando la segunda funcion hash, ya que es la que menos colisiones tiene,
diferenciando esta funcion de la tercera en este aspecto.


## Comparación de tiempos dados en milisegundos
Tiempo en realizar las búsquedas en la Tabla Hash:
Tiempo en realizar las búsquedas en la Lista: