# Chronix
A mod menu base for Grand Theft Auto V.

![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Online%20Version&query=%24.game.online&url=https%3A%2F%2Fbedrock.root.sx%2Fgitapi.php&style=flat-square&labelColor=000000)
![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Game%20Build&query=%24.game.build&url=https%3A%2F%2Fbedrock.root.sx%2Fgitapi.php&style=flat-square&labelColor=000000)

## STRICTLY FOR EDUCATIONAL PURPOSES

Chronix is originally based of off YimMenu which is based off of [BigBaseV2](https://github.com/Pocakking/BigBaseV2).  BigBaseV2 was an amazing base at the time but nowadays is a bit dated.
Chronix is an up-to-date menu focusing on protecting the user from toxic modders.

## Table of contents

 * [How to build](#how-to-build)
 * [Make your own flavour of YimMenu](#make-your-own-flavour-of-yimmenu)
 * [Staying Up To Date](#staying-up-to-date)
 * [Project Structure](#project-structure)
 * [Contributing](#contributing)
 
## How to compile Chronix
Read the [SETUP](https://github.com/YimMenu/YimMenu/wiki/Setup-your-PC-for-YimMenu-Development) guide.

## Staying Up To Date

Pull the latest changes from this repository.

With a command line it is as easy as:

```bash
git pull
```

CMake should be handling removed / added files automatically without any user input.

If this is not the case for some reason you'll have to redo the steps in the [Making changes to the source code section of the SETUP](https://github.com/YimMenu/YimMenu/wiki/Setup-your-PC-for-YimMenu-Development#making-changes-to-the-source-code).

If you are doing custom modifications to the codebase and have a fork you are on your own for staying up to date with upstream (this repository), google stuff like "merge from upstream" and learn how to use Git.

## Project Structure

- `backend/` all features that should be ran in a loop are in here sorted by category
- `gui/` includes everything related to UI elements
- `hooks/` function hooks
- `native_hooks/` hooks to natives
- `services/` service files to interact and maintain stuff
- `util/` general utility functions to keep code as compact and as much in one place as possible

## Contributing

You're free to contribute to Chronix as long as the features are useful, not overly toxic and do not contain ANYTHING related to GTA5 Source Code Leaks, or anything that may get Chronix targeted by Take2 or its affliliates.
## Contributions of code from ANY source code leaks will be removed and you will be banned from the repository, NO EXCEPTIONS!

Make sure to read the [CONTRIBUTING.md](CONTRIBUTING.md) file.
