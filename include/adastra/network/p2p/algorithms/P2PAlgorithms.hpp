#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace adastra::network::p2p::algorithms {

    struct PeerInfo {
        std::string id;
        std::string ip;
        int port;
        int score = 0;
    };

    class P2PAlgorithms {
    public:
        // Trouver le meilleur pair selon un score
        static std::optional<PeerInfo> selectBestPeer(const std::vector<PeerInfo>& peers);

        // Calculer le score d’un pair (ex: latence, fiabilité, disponibilité)
        static int computePeerScore(const PeerInfo& peer);

        // Répartir les données à synchroniser entre les pairs
        static std::unordered_map<std::string, std::vector<std::string>> distributeChunks(
            const std::vector<PeerInfo>& peers,
            const std::vector<std::string>& dataChunks
        );

        // Algorithme de réplication minimale (ex: 3 copies par chunk)
        static std::unordered_map<std::string, std::vector<std::string>> replicateChunks(
            const std::vector<std::string>& chunkIds,
            const std::vector<PeerInfo>& peers,
            int replicationFactor = 3
        );
    };

} // namespace adastra::network::p2p::algorithms
