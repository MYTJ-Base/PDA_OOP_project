# Packaging and Distribution Guide for PDA_OOP

Your project has been modernized with a CMake build system and GitHub Actions for automated packaging.

## How to Build Locally

```bash
# Create build directory
cmake -B build

# Compile
cmake --build build

# Run the app
./build/pda_app
```

## How to Distribute via GitHub Package Registry

The project is configured to automatically build and release a package whenever you push a version tag.

### 1. Tag a Version
When you are ready to release, tag your current commit:

```bash
git tag -a v1.0.0 -m "Release version 1.0.0"
```

### 2. Push the Tag
Push the tag to GitHub:

```bash
git push origin v1.0.0
```

### 3. Verification
- Go to the **Actions** tab in your GitHub repository.
- You will see a "CMake Build and Publish" workflow running.
- Once finished, a new release will be created under the **Releases** section with `pda-oop-assets.zip` containing the binaries and headers for both Linux and Windows.

## Project Structure Overview

- `src/`: Contains the core logic library (`pda_lib`). Headers and sources are kept together for simplicity.
- `app/`: Contains the application entry point (`main.cpp`).
- `data/`: Directory for persistent storage files.
- `CMakeLists.txt`: The modern build definition.
- `.github/workflows/`: Automated CI/CD pipelines.

## Cross-Platform Support
The CMake setup and GitHub Actions ensure that:
- The library and executable can be built on any system with a C++17 compiler and CMake.
- The CI pipeline verifies the build on both **Linux (Ubuntu)** and **Windows**.
