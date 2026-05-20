// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import "forge-std/Script.sol";
import "../src/ZionToken.sol";

/// @notice Deploy ZionToken to Sepolia.
/// Usage:
///   forge script script/Deploy.s.sol --rpc-url sepolia --broadcast --verify -vvvv
contract DeployZionToken is Script {
    function run() external {
        uint256 privateKey = vm.envUint("PRIVATE_KEY");
        // Derive deployer address directly from the private key
        address deployer = vm.addr(privateKey);

        vm.startBroadcast(privateKey);

        ZionToken token = new ZionToken(deployer);

        vm.stopBroadcast();

        console.log("ZionToken deployed at:", address(token));
        console.log("Admin / initial minter:", deployer);
        console.log("Network: Sepolia");
        console.log("");
        console.log("Next steps:");
        console.log("  1. Copy contract address to VITE_ZION_TOKEN_ADDRESS in transcendence-front/.env");
        console.log("  2. Call addMinter(<backend-wallet>) if you want the backend to mint");
    }
}
