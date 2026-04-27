local_repository(
    name = "splitfxmpp",
    path = "third-party/SplitFXMpp",
)

new_local_repository(
    name = "cantera",
    path = "third-party/SplitFXMpp/third-party/cantera",
    build_file = "@splitfxmpp//ext:cantera.BUILD",
)

local_repository(
    name = "splitopspp",
    path = "third-party/SplitFXMpp/third-party/SplitOPSpp",
)

local_repository(
    name = "splitdaepp",
    path = "third-party/SplitFXMpp/third-party/SplitOPSpp/third-party/SplitDAEpp",
)

local_repository(
    name = "splitnewtonpp",
    path = "third-party/SplitFXMpp/third-party/SplitOPSpp/third-party/SplitDAEpp/third-party/SplitNewtonpp",
)

new_local_repository(
    name = "mfem",
    path = "third-party/SplitFXMpp/third-party/MFEM",
    build_file = "@splitfxmpp//ext:mfem.BUILD",
)

new_local_repository(
    name = "raja",
    path = "third-party/SplitFXMpp/third-party/RAJA",
    build_file = "@splitfxmpp//ext:raja.BUILD",
)
