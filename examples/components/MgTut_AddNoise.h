#ifndef MEGAT_TUTURIAL_AddNoise_H
#define MEGAT_TUTURIAL_AddNoise_H

// GAUDI
#include "GaudiAlg/GaudiAlgorithm.h"
#include "Gaudi/Property.h"
#include "GaudiKernel/IRndmGenSvc.h"

// k4FWCore
#include "k4FWCore/DataHandle.h"

/** @class MgTut_AddNoise
 *
 *  This algorithm demo shows how to use the Gaudi random service to add a
 *  pedestal noise (in Gaussian) to calo hit energy.
 *
 *  See tut_addnoise.py for usage.
 *
 *  @author Yong Zhou
 */

namespace edm4hep { class SimCalorimeterHitCollection; }

class MgTut_AddNoise : public GaudiAlgorithm {
public:
  MgTut_AddNoise(const std::string&, ISvcLocator*);
  virtual ~MgTut_AddNoise();
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
  /// Pointer to the random numbers service
  ServiceHandle<IRndmGenSvc> m_randSvc;

  /// random generator parameters
  Gaudi::Property<float> m_mean{this, "Mean", 0.0, "Mean of Pedestal (in MeV)"};
  Gaudi::Property<float> m_sigma{this, "Sigma", 1.0, "Width of Pedestal (sigma in MeV)"};

  /// Handle to EDM collection
  DataHandle<edm4hep::SimCalorimeterHitCollection> m_inHits{"CztHits", Gaudi::DataHandle::Reader, this};
  DataHandle<edm4hep::SimCalorimeterHitCollection> m_outHits{"NoisyCztHits", Gaudi::DataHandle::Writer, this};
};
#endif /* MEGAT_TUTURIAL_AddNoise_H */
