﻿# INI-Parser

## Installation



## Example

``` 
#include "includes/ini.h"

int main() {

    std::string value;

    INI* ini = new INI("example.ini");

    // Check if Section exists
    if( !ini->sectionExists("Example"))
        std::cout << "Section [Example] does not exists." << std::endl;
    // Check if Key exists
    if( !ini->keyExists("Example", "address"))
        std::cout << "Key Address does not exists." << std::endl;

    // Get Key
    value = ini->getValue("Example", "author");
    std::cout << "Old Author: " << value << std::endl;

    // Write Key
    ini->writeValue("Example", "author", "Simon");

    // Get Key
    value = ini->getValue("Example", "author");
    std::cout << "New Author: " << value << std::endl;

    system("pause");
}

```

### Changelog

Please see [CHANGELOG](CHANGELOG.md) for more information what has changed recently.

## Contributing

Please see [CONTRIBUTING](CONTRIBUTING.md) for details.

### Security

If you discover any security related issues, please email linden@snerve.de instead of using the issue tracker.

## Credits

- [Simon Marcel Linden](https://github.com/SimonMarcelLinden)
- [All Contributors](../../contributors)

## License

Please see [License File](LICENSE.md) for more information.
