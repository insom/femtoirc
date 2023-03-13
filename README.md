femtoirc
========

An extremely small IRC client that really just responds to PINGs and logs in.

Designed to run under tmux with one pane for reading and one for writing.

```
make
```

![Screenshot](https://github.com/insom/femtoirc/blob/main/shot.png?raw=true)

To "chat" just `cat` or `echo` valid RFC 1459 commands to the pipe in the same directory.

If you `tmux` you probably want something like

```
bind-key -n S-Left "select-pane -L"
bind-key -n S-Down "select-pane -D"
bind-key -n S-Up "select-pane -U"
bind-key -n S-Right "select-pane -R"
set -g mouse
```

to keeps things even remotely ergonomic as you move between panes.

License
-------

Copyright (c) 2023, Aaron Brady

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
