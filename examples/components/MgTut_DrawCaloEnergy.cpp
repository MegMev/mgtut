#include "MgTut_DrawCaloEnergy.h"

// Gaudi
#include "GaudiKernel/ITHistSvc.h"

// edm4hep
#include "edm4hep/SimCalorimeterHitCollection.h"

// others
#include "TH1F.h"

DECLARE_COMPONENT(MgTut_DrawCaloEnergy)

MgTut_DrawCaloEnergy::MgTut_DrawCaloEnergy(const std::string &aName, ISvcLocator *aSvcLoc)
: GaudiAlgorithm(aName, aSvcLoc), m_histSvc("THistSvc", aName){
  declareProperty("InHits", m_caloHits,
                  "Input Hit Collection of Calorimeter");
}
MgTut_DrawCaloEnergy::~MgTut_DrawCaloEnergy() {}

StatusCode MgTut_DrawCaloEnergy::initialize() {
  /// mandatory
  if (GaudiAlgorithm::initialize().isFailure()) return StatusCode::FAILURE;

  /// services
  if (!m_histSvc) {
    error() << "Unable to locate Histogram Service" << endmsg;
    return StatusCode::FAILURE;
  }

  // register histograms
  std::unique_ptr<TH1F> h1 = std::make_unique<TH1F>( m_name.value().data(), m_name.value().data(),
                                                     m_bins, 0, m_range);
  if ( m_histSvc->regHist( "/tutorial"+m_dir+"/"+m_name, std::move(h1) ).isFailure() ) {
    error() << "Couldn't register " << m_name << endmsg;
    return StatusCode::FAILURE;
  }

  return StatusCode::SUCCESS;
}

StatusCode MgTut_DrawCaloEnergy::execute() {
  /// fetch the histogram
  TH1 *h(nullptr);
  if (!m_histSvc->getHist("/tutorial"+m_dir+"/"+m_name, h).isSuccess()) {
    error() << "Couldn't retrieve histogram " << m_dir+"/"+m_name << endmsg;
  }

  /// fetch the hit collection and fill
  const auto calo_hits = m_caloHits.get();
  for (const auto &hit : *calo_hits) {
    h->Fill(1000 * hit.getEnergy());
  }

  return StatusCode::SUCCESS;
}

StatusCode MgTut_DrawCaloEnergy::finalize() { return GaudiAlgorithm::finalize(); }
