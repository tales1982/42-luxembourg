package com.transcendence.blockchain;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.web3j.abi.FunctionEncoder;
import org.web3j.abi.datatypes.Address;
import org.web3j.abi.datatypes.Function;
import org.web3j.abi.datatypes.generated.Uint256;
import org.web3j.crypto.Credentials;
import org.web3j.protocol.Web3j;
import org.web3j.protocol.core.methods.response.EthSendTransaction;
import org.web3j.protocol.http.HttpService;
import org.web3j.tx.RawTransactionManager;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Collections;

@Slf4j
@Service
@RequiredArgsConstructor
public class BlockchainService {

    private final BlockchainProperties props;

    /**
     * Mint ZION tokens directly to the worker's wallet as task reward.
     *
     * @param toAddress  Worker's Ethereum wallet address.
     * @param amount     Reward amount in ZION (human-readable, e.g. 250).
     * @param taskId     Backend task ID for on-chain correlation.
     * @return Transaction hash, or null if mint was skipped / failed.
     */
    public String mintTaskReward(String toAddress, BigDecimal amount, Long taskId) {
        if (props.getMinterPrivateKey() == null || props.getMinterPrivateKey().isBlank()) {
            log.warn("BLOCKCHAIN_MINTER_KEY not configured – skipping on-chain mint for task {}", taskId);
            return null;
        }
        if (props.getContractAddress() == null || props.getContractAddress().isBlank()) {
            log.warn("ZION_TOKEN_ADDRESS not configured – skipping on-chain mint for task {}", taskId);
            return null;
        }

        try {
            Web3j web3j = Web3j.build(new HttpService(props.getRpcUrl()));
            Credentials credentials = Credentials.create(props.getMinterPrivateKey());

            // Convert ZION amount to wei (18 decimals)
            BigInteger amountWei = amount
                    .multiply(BigDecimal.TEN.pow(18))
                    .toBigInteger();

            // Encode mintReward(address to, uint256 amount, uint256 taskId)
            Function function = new Function(
                    "mintReward",
                    Arrays.asList(
                            new Address(toAddress),
                            new Uint256(amountWei),
                            new Uint256(BigInteger.valueOf(taskId))
                    ),
                    Collections.emptyList()
            );
            String encodedFunction = FunctionEncoder.encode(function);

            RawTransactionManager txManager = new RawTransactionManager(
                    web3j, credentials, props.getChainId());

            BigInteger gasPrice = web3j.ethGasPrice().send().getGasPrice();
            BigInteger gasLimit = BigInteger.valueOf(200_000L);

            EthSendTransaction txResponse = txManager.sendTransaction(
                    gasPrice, gasLimit,
                    props.getContractAddress(),
                    encodedFunction,
                    BigInteger.ZERO
            );

            if (txResponse.hasError()) {
                log.error("Blockchain mintReward error for task {}: {}",
                        taskId, txResponse.getError().getMessage());
                return null;
            }

            String txHash = txResponse.getTransactionHash();
            log.info("Minted {} ZION to {} for task {} – txHash: {}", amount, toAddress, taskId, txHash);
            return txHash;

        } catch (Exception e) {
            log.error("Failed to mint tokens on-chain for task {}: {}", taskId, e.getMessage());
            return null;
        }
    }
}
