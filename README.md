# IRCI - Repositorio Unificado

Repositorio principal que unifica todos los trabajos prácticos, implementaciones y proyectos de la materia utilizando **Git Submodules**.

---

## 📦 Submódulos Vinculados

Cada una de las siguientes carpetas está vinculada como un submódulo a su repositorio original correspondiente:

- **[`Branch-Zero`](https://github.com/Matuti2611/Branch-Zero)**: Documentación y diseño en simulación del circuito de detección y salto condicional Branch Zero (BRZ) y Zero Flag (`Zero Flag.cv`).
- **[`intrucciones-cpu-c`](https://github.com/Matuti2611/intrucciones-cpu-c)**: Implementación y simulación de la CPU e instrucciones en lenguaje C (`hola.c`).
- **[`instrucciones-procesador`](https://github.com/Matuti2611/instrucciones-procesador)**: Casos de prueba y documentación de la ejecución de instrucciones aritméticas, lógicas y de control del procesador.
- **[`Trabajo-BCMS`](https://github.com/Matuti2611/Trabajo-BCMS)**: Proyecto y diseño del juego Arkanoid, historia, mecánicas y assets gráficos/sprites.

### 📄 Archivos y Proyectos Locales

- **[`pintar-assembly/`](./pintar-assembly)**: Programa interactivo en código ensamblador MIPS (`pintar.rtm`) que interactúa mediante MMIO con la consola capturando teclas de movimiento (WASD, Enter, Backspace) para manipular el cursor y pintar o borrar píxeles en pantalla.

---

## 🔄 Sincronización Automática

Este repositorio cuenta con un flujo de trabajo automatizado en **GitHub Actions** (`.github/workflows/update-submodules.yml`) que:
- Revisa diariamente y actualiza los submódulos a su último commit en la rama `main`.
- Permite actualizar todos los submódulos manualmente en cualquier momento desde la pestaña **Actions** > **Actualizar Submódulos** > **Run workflow**.

---

## 📥 Cómo clonar este repositorio con sus submódulos

Para clonar este repositorio junto con el contenido completo de todos sus submódulos:

```bash
git clone --recurse-submodules https://github.com/Matuti2611/irci.git
```

Si ya lo clonaste sin la bandera `--recurse-submodules`, puedes inicializarlos y descargarlos con:

```bash
git submodule update --init --recursive
```