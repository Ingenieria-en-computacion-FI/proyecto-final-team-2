import subprocess
import time
import os
import pandas as pd
import matplotlib.pyplot as plt

results = []
sizes = [100, 500, 1000, 5000]

# Asegurar que los directorios de destino existan
os.makedirs("reports/csv", exist_ok=True)
os.makedirs("reports/graphs", exist_ok=True)

# Ejecución del Benchmark llamando a tu binario en C
for size in sizes:
    start = time.time()

    subprocess.run([
        "./bin/main",
        str(size)
    ])

    end = time.time()
    results.append({
        "size": size,
        "time": end - start
    })

# Guardar los datos en el DataFrame y exportar a CSV (Lógica de la Profra.)
df = pd.DataFrame(results)
df.to_csv("reports/csv/benchmark.csv", index=False)
print("✅ Datos guardados en reports/csv/benchmark.csv")

# ==============================================================================
# 📊 BLOQUE AÑADIDO: GENERACIÓN AUTOMÁTICA DE LA GRÁFICA
# ==============================================================================
plt.figure(figsize=(8, 5))
plt.plot(df["size"], df["time"], marker="o", linestyle="-", color="b", label="Tiempo de ejecución")
plt.title("Análisis de Rendimiento del Simulador (Benchmarking)")
plt.xlabel("Cantidad de Procesos (Tamaño de Carga)")
plt.ylabel("Tiempo de Ejecución (segundos)")
plt.grid(True, linestyle="--", alpha=0.6)
plt.legend()

# Guardar la gráfica exactamente en la carpeta que creamos
plt.savefig("reports/graphs/benchmark_performance.png", dpi=300)
plt.close()
print("📊 ¡Gráfica exportada exitosamente en reports/graphs/benchmark_performance.png!")