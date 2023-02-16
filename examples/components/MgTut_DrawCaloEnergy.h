#ifndef MEGAT_MgTut_DrawCaloEnergy_H
#define MEGAT_MgTut_DrawCaloEnergy_H

// GAUDI
#include "GaudiAlg/GaudiAlgorithm.h"

// k4FWCore
#include "k4FWCore/DataHandle.h"

/** @class MgTut_DrawCaloEnergy
 *
 * This algorithm demo shows how to use Gaudi's histogram service (THistSvc)
 * to book, fill and save a histogram of desopsit energy for the input collections.
 * Collection need to be loaded into TES already, here only collection names are
 * configured.
 *
 * See tut_addnoise.py for usage.
 *
 *  @author Yong Zhou
 */

class ITHistSvc;
class TH1F;

// uncomment the edm collection you need
namespace edm4hep {
  class SimCalorimeterHitCollection;
}

class MgTut_DrawCaloEnergy : public GaudiAlgorithm {
public:
  MgTut_DrawCaloEnergy(const std::string&, ISvcLocator*);
  virtual ~MgTut_DrawCaloEnergy();
  /**  Initialize.
   *   @return status code
   */
  virtual StatusCode initialize() final;
  /**  Fills the histograms.
   *   @return status code
   */
  virtual StatusCode execute() final;
  /**  Finalize.
   *   @return status code
   */
  virtual StatusCode finalize() final;

private:
  /// Pointer to the interface of histogram service
  ServiceHandle<ITHistSvc> m_histSvc;

  /// Handle to EDM collection
  DataHandle<edm4hep::SimCalorimeterHitCollection> m_caloHits{"CztHits", Gaudi::DataHandle::Reader, this};

  /// Properties
  Gaudi::Property<std::string> m_name{this, "HistName", "hCaloE", "Name of the histogram"};
  Gaudi::Property<std::string> m_dir{this, "HistDir", "/", "Directory of the histogram in TFile"};
  Gaudi::Property<float> m_range{this, "HistRange", 30, "Higher range of histogram axis in MeV"};
  Gaudi::Property<int>   m_bins{this, "HistBins", 300, "Bin number of histogram axis"};
};
#endif /* MEGAT_MgTut_DrawCaloEnergy_H */
