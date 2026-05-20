package com.transcendence.blockchain;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Data
@Component
@ConfigurationProperties(prefix = "blockchain")
public class BlockchainProperties {

    /** Alchemy / Infura RPC URL for Sepolia */
    private String rpcUrl;

    /** ZionToken contract address on Sepolia */
    private String contractAddress;

    /** Private key of the wallet with MINTER_ROLE (hex, with 0x prefix) */
    private String minterPrivateKey;

    /** Sepolia chain ID */
    private long chainId = 11155111L;
}
