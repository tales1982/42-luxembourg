// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import "@openzeppelin/contracts/token/ERC20/ERC20.sol";
import "@openzeppelin/contracts/access/AccessControl.sol";

/// @title ZionToken
/// @notice ERC-20 token used as reward for completed tasks on the Transcendence platform.
/// @dev Only addresses with MINTER_ROLE can mint tokens (e.g. the backend signer wallet).
contract ZionToken is ERC20, AccessControl {
    bytes32 public constant MINTER_ROLE = keccak256("MINTER_ROLE");

    event TokensMinted(address indexed to, uint256 amount, uint256 taskId);
    event TokensBurned(address indexed from, uint256 amount);

    constructor(address admin) ERC20("Zion Token", "ZION") {
        _grantRole(DEFAULT_ADMIN_ROLE, admin);
        _grantRole(MINTER_ROLE, admin);
    }

    /// @notice Mint tokens as reward for a completed task.
    /// @param to      Recipient wallet address (task worker).
    /// @param amount  Amount in wei (18 decimals).
    /// @param taskId  Backend task ID for off-chain correlation.
    function mintReward(address to, uint256 amount, uint256 taskId) external onlyRole(MINTER_ROLE) {
        _mint(to, amount);
        emit TokensMinted(to, amount, taskId);
    }

    /// @notice Mint tokens without task reference (admin use / initial supply).
    function mint(address to, uint256 amount) external onlyRole(MINTER_ROLE) {
        _mint(to, amount);
    }

    /// @notice Burn caller's own tokens.
    function burn(uint256 amount) external {
        _burn(msg.sender, amount);
        emit TokensBurned(msg.sender, amount);
    }

    /// @notice Grant MINTER_ROLE to a backend wallet.
    function addMinter(address minter) external onlyRole(DEFAULT_ADMIN_ROLE) {
        _grantRole(MINTER_ROLE, minter);
    }

    /// @notice Revoke MINTER_ROLE from an address.
    function removeMinter(address minter) external onlyRole(DEFAULT_ADMIN_ROLE) {
        _revokeRole(MINTER_ROLE, minter);
    }
}
