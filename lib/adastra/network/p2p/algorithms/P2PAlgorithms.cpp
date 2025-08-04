#include <algorithm>
#include <random>
#include <adastra/network/p2p/algorithms/P2PAlgorithms.hpp>

namespace adastra::network::p2p::algorithms {

std::optional<PeerInfo> P2PAlgorithms::selectBestPeer(const std::vector<PeerInfo>& peers) {
    if (peers.empty()) return std::nullopt;

    return *std::max_element(peers.begin(), peers.end(), [](const PeerInfo& a, const PeerInfo& b) {
        return a.score < b.score;
    });
}

int P2PAlgorithms::computePeerScore(const PeerInfo& peer) {
    return peer.score;
}

std::unordered_map<std::string, std::vector<std::string>> P2PAlgorithms::distributeChunks(
    const std::vector<PeerInfo>& peers,
    const std::vector<std::string>& dataChunks
) {
    std::unordered_map<std::string, std::vector<std::string>> assignments;
    int index = 0;

    for (const auto& chunk : dataChunks) {
        if (peers.empty()) break;
        const PeerInfo& assignedPeer = peers[index % peers.size()];
        assignments[assignedPeer.id].push_back(chunk);
        ++index;
    }

    return assignments;
}

std::unordered_map<std::string, std::vector<std::string>> P2PAlgorithms::replicateChunks(
    const std::vector<std::string>& chunkIds,
    const std::vector<PeerInfo>& peers,
    int replicationFactor
) {
    std::unordered_map<std::string, std::vector<std::string>> replicationMap;
    std::vector<std::string> peerIds;

    for (const auto& peer : peers)
        peerIds.push_back(peer.id);

    std::shuffle(peerIds.begin(), peerIds.end(), std::mt19937{std::random_device{}()});

    for (const auto& chunk : chunkIds) {
        for (int i = 0; i < replicationFactor && i < (int)peerIds.size(); ++i) {
            replicationMap[peerIds[i]].push_back(chunk);
        }
        std::rotate(peerIds.begin(), peerIds.begin() + 1, peerIds.end());
    }

    return replicationMap;
}

} // namespace adastra::network::p2p::algorithms
