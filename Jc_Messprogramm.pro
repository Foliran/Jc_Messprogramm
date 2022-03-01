TEMPLATE = subdirs

SUBDIRS += \
    Control \
    ControlCore \
    Instruments \
    Core \
    Viewer

Core.depends=Instruments
ControlCore.depends=Core
Control.depends=ControlCore
Viewer.depends=Core
