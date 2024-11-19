#include <pch.h>
#include <wx/filefn.h>
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    return RUN_ALL_TESTS();
}
