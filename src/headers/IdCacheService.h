#pragma once

#include "EnumTypes.h"

#include <unordered_map>
#include <mutex>
#include <cstdint>
#include <atomic>


// --- Hash custom for pair<int, EntityType> ---
struct PairHash {
	std::size_t operator()(const std::pair<int32_t, EntityType>& p) const noexcept {
		auto h1 = std::hash<int32_t>{}(p.first);
		auto h2 = std::hash<int32_t>{}(static_cast<int32_t>(p.second));
		
		return h1 ^ (h2 << 1);
	}
};


class IdCacheService {
private:
	std::unordered_map<EntityType, std::atomic<int32_t>>					local_temp_ids;
	std::unordered_map<std::pair<int32_t, EntityType>, int32_t, PairHash>   id_mapping; // local_id, EntityType -> real_id
	mutable std::mutex mtx;

public:
	IdCacheService() {
		local_temp_ids[EntityType::TASK] = -1;
		local_temp_ids[EntityType::CATEGORY] = -1;
		local_temp_ids[EntityType::USER] = -1;
		local_temp_ids[EntityType::COMMENT] = -1;
	}
	// cand adaug task coment etc nou decrementez id-ul local pentru cache mai departe
	int32_t next_temp_id(EntityType type) {
		return local_temp_ids[type]--;
	}
	// inregistrez id local ii atribui valoarea reala din DB
	void register_mapping(int32_t local_id, uint32_t real_id, EntityType eType) {
		std::lock_guard<std::mutex> lock(mtx);
		id_mapping[{local_id, eType}] = real_id;
	}
	// verificare daca exista id local
	bool has_mapping(int32_t local_id, EntityType eType) const {
		std::lock_guard<std::mutex> lock(mtx);
		return id_mapping.count({local_id, eType}) > 0;
	}
	// returnez id real pentru cel stocat local. se foloseste la sincronizare date
	int32_t get_real_id(int32_t local_id, EntityType eType) const {
		std::lock_guard<std::mutex> lock(mtx);
		if (auto it = id_mapping.find({ local_id, eType }); it != id_mapping.end())
			return it->second;
		return local_id;
	}
}; extern IdCacheService CacheService_;
