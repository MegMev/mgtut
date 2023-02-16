#include "MgTut_AddNoise.h"

// Gaudi
#include "GaudiKernel/RndmGenerators.h"

// edm4hep
#include "edm4hep/SimCalorimeterHitCollection.h"

DECLARE_COMPONENT(MgTut_AddNoise)

MgTut_AddNoise::MgTut_AddNoise(const std::string &aName, ISvcLocator *aSvcLoc)
: GaudiAlgorithm(aName, aSvcLoc), m_randSvc("RndmGenSvc", aName){
  declareProperty("InHits", m_inHits,
                  "Input Hit Collection of Calorimeter");
  declareProperty("OutHits", m_outHits,
                  "Output Hit Collection of Calorimeter with Pedestal");
}
MgTut_AddNoise::~MgTut_AddNoise() {}

StatusCode MgTut_AddNoise::initialize() {
  /// mandatory
  if (GaudiAlgorithm::initialize().isFailure()) return StatusCode::FAILURE;

  // fetch services
  if (!m_randSvc) {
    error() << "Unable to locate RndmGen Service" << endmsg;
    return StatusCode::FAILURE;
  }
  return StatusCode::SUCCESS;
}

StatusCode MgTut_AddNoise::execute() {
  // [Improve] have to use get(), no conversion operator implementation in GaudiHandle
  Rndm::Numbers gauss( m_randSvc.get(), Rndm::Gauss( m_mean, m_sigma ) );

  /// fetch the hit collection and fill
  auto noisy_hits = m_outHits.createAndPut();
  const auto calo_hits = m_inHits.get();
  for (const auto &hit : *calo_hits) {
    auto new_hit = hit.clone();
    new_hit.setEnergy(gauss() * 0.001 + hit.getEnergy());
    noisy_hits->push_back(new_hit); // noisy_hits now owns the new_hit
  }

  return StatusCode::SUCCESS;
}

StatusCode MgTut_AddNoise::finalize() { return GaudiAlgorithm::finalize(); }
