# G510s
Graphical utility for Logitech G510 and G510s keyboards on Linux.

Requires LibG15 found here: https://github.com/vividnightmare/libg15  
You may use a different version of libg15, but it will have some issues with these keyboards.  
I would send the fixes upstream, but upstream doesn't appear to exist anymore.

There is an Ubuntu PPA available here: https://launchpad.net/~vivnet/+archive/ubuntu/g510s  
It currently has packages published for Xenial (16.04), Bionic (18.04), and Cosmic (18.10).  
If you would like me to add packages for a different release, open an issue and let me know which one, I would be happy to publish packages for any currently supported Ubuntu release.

# Build Deps
  * libg15-dev
  * libg15render-dev
  * libappindicator3-dev
  * libgtk-3-dev

# TODO
  * Valgrind
  * New icon
  * DBUS IPC
  * Save on system shutdown
  * Launch screens from GUI
