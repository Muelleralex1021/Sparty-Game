project(ConveyorLib)

set(SOURCE_FILES
        MainFrame.cpp
        MainFrame.hpp
        SpartyBootsView.cpp
        SpartyBootsView.hpp
        SpartyBoots.cpp
        SpartyBoots.hpp
        Item.cpp
        Item.hpp
        Conveyor.cpp
        Conveyor.hpp
        ids.hpp
        OrGate.cpp
        OrGate.hpp
        LoadLevel.cpp
        LoadLevel.h
        ScoreBoard.cpp
        ScoreBoard.hpp
        Sensor.cpp
        Sensor.h
        Product.cpp
        Product.h
        Beam.cpp
        Beam.hpp
        Sparty.cpp
        Sparty.hpp
        AndGate.cpp
        AndGate.hpp
        NotGate.cpp
        NotGate.hpp
        LogicItem.cpp
        LogicItem.hpp
        LogicGate.cpp
        LogicGate.cpp
        LogicGate.h
        ItemVisitor.cpp
        ItemVisitor.hpp
        ProductUpdateVisitor.cpp
        ProductUpdateVisitor.hpp
        LastProductVisitor.cpp
        LastProductVisitor.hpp
        InputPin.cpp
        InputPin.h
        OutputPin.cpp
        OutputPin.h
        IDraggable.h
        PinConnector.cpp
        PinConnector.h
        PinConnector.cpp
        SRFlipFlop.cpp
        SRFlipFlop.h
        DFlipFlop.cpp
        DFlipFlop.h
        DFlipFlop.cpp)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)