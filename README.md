CriptoApp - Segundo Parcial QT

> Aplicación de escritorio desarrollada en Qt para cifrado y descifrado de archivos de texto utilizando múltiples algoritmos criptográficos.

## 🧠 ¿Qué hace esta app?

CriptoApp permite **cifrar y descifrar archivos .txt** usando los siguientes algoritmos:

| Algoritmo        | Cifrado | Descifrado | Detalles                           |
|------------------|:-------:|:----------:|------------------------------------|
| César            | ✅      | ✅         | Con desplazamiento modificable.   |
| ASCII → Binario  | ✅      | ✅         | Convierte texto a binario y viceversa. |
| DES              | ✅      | ✅         | Usa clave fija de 64 bits.        |
| XOR Encoder      | ✅      | ✅         | Requiere clave del usuario.       |
| Vigenère         | ✅      | ✅         | Requiere clave del usuario.       |

---

## 🖥️ Captura de la Interfaz

<img src="https://github.com/user-attachments/assets/5dfd832d-d8e3-4297-9fa4-c8e73d4a54ef" width="600">

---

## 📦 Release

🎉 La versión ejecutable de CriptoApp está disponible en la sección de [Releases](https://github.com/69-bits/CriptoAnalisis/releases) como un archivo `.zip`.

> ⚠️ Solo necesitas descargar, descomprimir y ejecutar `CriptoApp.exe`.

---

## 🚀 ¿Cómo usarlo?

1. Selecciona el modo `Cifrar` o `Descifrar`.
2. Elige el tipo de cifrado.
3. Carga un archivo `.txt` (¡o cualquier tipo si lo has modificado!).
4. Si el algoritmo lo requiere, introduce una clave.
5. Presiona el botón de acción.
6. Guarda el resultado con el botón inferior.

---

## 🛠️ Requisitos

Si deseas compilar el proyecto por tu cuenta:

- Qt 6.x (con Qt Creator o Qt en consola)
- `windeployqt` si quieres generar tu ejecutable portable
- MinGW (si usas compilador por defecto)

---

## 💾 Estructura de carpetas
├── CriptoApp/ # Código fuente principal
│ ├── mainwindow.cpp
│ ├── Vigenere.h
│ └── ...
├── build/ # Carpeta de compilación
├── releases/ # Ejecutables .zip


