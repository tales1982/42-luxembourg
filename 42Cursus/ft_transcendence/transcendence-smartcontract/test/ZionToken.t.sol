// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import "forge-std/Test.sol";
import "../src/ZionToken.sol";

contract ZionTokenTest is Test {
    // Mirror events to use with vm.expectEmit
    event TokensMinted(address indexed to, uint256 amount, uint256 taskId);
    event TokensBurned(address indexed from, uint256 amount);
    ZionToken public token;

    address public admin   = address(0xA0);
    address public minter  = address(0xA1);
    address public worker  = address(0xA2);
    address public stranger = address(0xA3);

    function setUp() public {
        vm.prank(admin);
        token = new ZionToken(admin);
    }

    // ─── Deployment ───────────────────────────────────────────────────────────

    function test_name() public view {
        assertEq(token.name(), "Zion Token");
    }

    function test_symbol() public view {
        assertEq(token.symbol(), "ZION");
    }

    function test_decimals() public view {
        assertEq(token.decimals(), 18);
    }

    function test_adminHasMinterRole() public view {
        assertTrue(token.hasRole(token.MINTER_ROLE(), admin));
    }

    function test_adminHasAdminRole() public view {
        assertTrue(token.hasRole(token.DEFAULT_ADMIN_ROLE(), admin));
    }

    // ─── Minting ──────────────────────────────────────────────────────────────

    function test_adminCanMint() public {
        vm.prank(admin);
        token.mint(worker, 100 ether);
        assertEq(token.balanceOf(worker), 100 ether);
    }

    function test_adminCanMintReward() public {
        vm.prank(admin);
        vm.expectEmit(true, false, false, true);
        emit TokensMinted(worker, 50 ether, 42);
        token.mintReward(worker, 50 ether, 42);
        assertEq(token.balanceOf(worker), 50 ether);
    }

    function test_strangerCannotMint() public {
        vm.prank(stranger);
        vm.expectRevert();
        token.mint(worker, 100 ether);
    }

    // ─── AddMinter / RemoveMinter ──────────────────────────────────────────────

    function test_adminCanAddMinter() public {
        vm.prank(admin);
        token.addMinter(minter);
        assertTrue(token.hasRole(token.MINTER_ROLE(), minter));
    }

    function test_newMinterCanMint() public {
        vm.prank(admin);
        token.addMinter(minter);

        vm.prank(minter);
        token.mint(worker, 200 ether);
        assertEq(token.balanceOf(worker), 200 ether);
    }

    function test_adminCanRemoveMinter() public {
        vm.prank(admin);
        token.addMinter(minter);

        vm.prank(admin);
        token.removeMinter(minter);
        assertFalse(token.hasRole(token.MINTER_ROLE(), minter));
    }

    function test_removedMinterCannotMint() public {
        vm.prank(admin);
        token.addMinter(minter);

        vm.prank(admin);
        token.removeMinter(minter);

        vm.prank(minter);
        vm.expectRevert();
        token.mint(worker, 100 ether);
    }

    function test_strangerCannotAddMinter() public {
        vm.prank(stranger);
        vm.expectRevert();
        token.addMinter(stranger);
    }

    // ─── Burn ─────────────────────────────────────────────────────────────────

    function test_holderCanBurn() public {
        vm.prank(admin);
        token.mint(worker, 100 ether);

        vm.prank(worker);
        vm.expectEmit(true, false, false, true);
        emit TokensBurned(worker, 40 ether);
        token.burn(40 ether);

        assertEq(token.balanceOf(worker), 60 ether);
    }

    function test_cannotBurnMoreThanBalance() public {
        vm.prank(admin);
        token.mint(worker, 10 ether);

        vm.prank(worker);
        vm.expectRevert();
        token.burn(20 ether);
    }

    // ─── Transfer ─────────────────────────────────────────────────────────────

    function test_transfer() public {
        vm.prank(admin);
        token.mint(worker, 100 ether);

        vm.prank(worker);
        token.transfer(stranger, 30 ether);

        assertEq(token.balanceOf(worker),   70 ether);
        assertEq(token.balanceOf(stranger), 30 ether);
    }

    function test_totalSupplyUpdatesOnMintAndBurn() public {
        vm.prank(admin);
        token.mint(worker, 100 ether);
        assertEq(token.totalSupply(), 100 ether);

        vm.prank(worker);
        token.burn(25 ether);
        assertEq(token.totalSupply(), 75 ether);
    }
}
