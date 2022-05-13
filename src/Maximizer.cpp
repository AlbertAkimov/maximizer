/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <stdio.h>
#include <wchar.h>
#include "Maximizer.h"

std::string MaximizerAddIn::extensionName() {
    return "Maximizer";
}

MaximizerAddIn::MaximizerAddIn() {

    AddProperty(L"Version", L"ВерсияКомпоненты", [&]() {
        auto s = std::string(Version);
        return std::make_shared<variant_t>(std::move(s));
    });

    AddMethod(L"maximizeWindow", L"РазвернутьОкно", this, &MaximizerAddIn::maximizeWindow);
}

void MaximizerAddIn::maximizeWindow(variant_t &name) {

    std::u16string nameForm1c = std::get<std::u16string>(name);

    for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
    {
        if (!IsWindowVisible(hwnd))
            continue;

        int length = GetWindowTextLength(hwnd);
        if (length == 0)
            continue;

        WCHAR* title = new WCHAR[length + 1];
        GetWindowTextW(hwnd, title, length + 1);

        if (0 == wcscmp(title, (wchar_t*)nameForm1c.c_str())) {
            ::ShowWindow(hwnd, SW_SHOWMAXIMIZED);
            break;
        }
    }
}
