import matplotlib
matplotlib.use('Qt5Agg')  # Set the backend to Qt5Agg

import matplotlib.pyplot as plt

import numpy as np

# Definir el rango de números

min_distance = 27.9 
max_distance = 29.7

# Generar 10 puntos uniformemente distribuidos en el rango para el histograma

puntos = np.linspace(min_distance, max_distance, num = 10)

# Distancias y frecuencias proporcionadas
distancias = puntos
frecuencias = [4, 35, 230, 663, 1235, 1456, 878, 359, 85, 5]
print("Puntos uniformemente distribuidos:", puntos)

# Crear el histograma
plt.bar(distancias, frecuencias, width=0.075, align='center')

# Etiquetas y título
plt.xlabel('Distancia')
plt.ylabel('Frecuencia')
plt.title('Histograma de las distancias entre puntos con dimension 5000')

plt.grid(True, linestyle='--', linewidth=0.5, color='gray')

plt.yticks(np.arange(min(frecuencias), max(frecuencias)+1, 200))
plt.xticks(np.arange(0, max_distance+4, 4))

# Mostrar el histograma
plt.show()
