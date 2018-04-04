# SPMod [![License](https://img.shields.io/badge/License-GPLv3-brightgreen.svg?style=flat-square)](LICENSE) [![Travis branch](https://img.shields.io/travis/Amaroq7/SPMod.svg?style=flat-square)](https://travis-ci.org/Amaroq7/SPMod)
SourcePawn Scripting Engine for Half-Life 1 based games

## About

SPMod is a [Metamod's](https://github.com/theAsmodai/metamod-r) plugin which is intended to be used as plugin system for Half-Life 1 and its derivatives. It uses [SourcePawn](https://github.com/alliedmodders/sourcepawn) as scripting language and allows to change completely the rules of a game or can ease the server administration by adding commands. SPMod's abilities can be extended by writing extensions, known as modules.

## Supported games & mods (in future)
* Half-Life
* Counter-Strike
* Counter-Strike: Condition Zero
* Day of Defeat
* Team Fortress Classic

For unsupported mods and games, check [here](https://github.com/Amaroq7/SPMod/wiki/Unsupported-games).

### Example plugin

```sourcepawn
struct PluginInfo
{
   public const char[] name;
   public const char[] version;
   public const char[] author;
   public const char[] url;
};

public PluginInfo pluginInfo =
{
	name = "test",
	version = "0.0.0",
	author = "author",
	url = "https://github.com/Amaroq7/SPMod"
};

native printToConsole(const char[] text);
forward void pluginInit();

public void pluginInit()
{
    printToConsole("Test output\n");
}
```

## Requirements
- ReHLDS (API v3.4)
- Metamod
  - [Metamod-r](https://github.com/theAsmodai/metamod-r) (recommended)
  - [Metamod-P](http://metamod-p.sourceforge.net)
  - [Metamod-am](https://www.amxmodx.org/downloads.php)

## Building

#### Linux
[Instructions to build SPMod for Linux](https://github.com/Amaroq7/SPMod/wiki/Building-SPMod-on-Linux)

#### Windows
[Instructions to build SPMod for Windows](https://github.com/Amaroq7/SPMod/wiki/Building-SPMod-on-Windows)

## API Reference

API is still in development, it'll be located on project's wiki.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [releases](https://github.com/Amaroq7/SPMod/releases).

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## License

SPMod is licensed under the General Public License version 3 - see the [LICENSE](LICENSE) file for details.
