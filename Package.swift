// swift-tools-version:5.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "tidy-html5",
    products: [
        .library(
            name: "tidy-html5",
            targets: ["tidy-html5"]),
    ],
    dependencies: [
       
    ],
    targets: [
        .target(name: "tidy-html5",
                dependencies: [],
                path: ".",
                exclude: [],
                sources: ["src"],
                publicHeadersPath: "include",
                cSettings: nil,
                cxxSettings: nil,
                swiftSettings: nil,
                linkerSettings: nil),
    ]
)
