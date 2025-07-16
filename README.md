# 🐚 minishell

<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/minishelle.png" alt="Minishell Badge" />
</p>

> A minimal shell, made from scratch in C, as part of the 42 school curriculum.

Minishell is a Unix-like command line interpreter built in C. It replicates a subset of Bash features, including pipelines, redirections, environment variable expansions, and essential built-in commands like `cd`, `echo`, `env`, and more.

---

## ✅ Project Status

* **Grade:** 101%
* **Validated On:** 2025-07-08

---

## 🚀 Getting Started

### Clone the repository :

```bash
git clone https://github.com/Mohamedamineelkhalloufi/minishell
```

### Build:

```bash
cd minishell && make
```

### Run:

```bash
./minishell
```

You'll get a prompt where you can enter and execute commands.

---

## ⚙️ Features

Minishell supports a range of functionalities to mimic Bash behavior:

### 🔧 Built-in Commands

* `echo` with `-n` option
* `cd` with relative or absolute paths
* `pwd`
* `export`
* `unset`
* `env`
* `exit` with optional exit code

### 📤 Redirections

* `>` : redirect output
* `>>` : append output
* `<` : redirect input
* `<<` : heredoc

### 🔗 Pipes

* `|` : connect commands by passing output as input

### 🌱 Environment

* Variable expansion: `$USER`, `$VAR`, `$?` (last exit code)

### ⌨️ Signal Handling

* `Ctrl-C` : interrupts and displays new prompt
* `Ctrl-D` : exits shell
* `Ctrl-\` : ignored

### ❌ Not Supported

* `\`, `;`, `&&`, `||`, wildcard expansion
