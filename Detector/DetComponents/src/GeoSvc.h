#ifndef K4SIMGEANT4_GEOSVC_H
#define K4SIMGEANT4_GEOSVC_H

#include <Gaudi/Property.h>
#include <GaudiKernel/Service.h>

#include "k4Interface/IGeoSvc.h"

namespace dd4hep {
class Detector;
}
class G4VUserDetectorConstruction;

class GeoSvc : public extends<Service, IGeoSvc> {

public:
  using base_class::base_class;

  /// Destructor
  virtual ~GeoSvc();
  /// Initialize function
  virtual StatusCode initialize() final override;
  /// This function generates the DD4hep geometry
  StatusCode buildDD4HepGeo();
  // This function generates the Geant4 geometry
  StatusCode buildGeant4Geo();
  // receive DD4hep Geometry
  virtual dd4hep::DetElement getDD4HepGeo() override;
  virtual const dd4hep::Detector* getDetector() const override;
  virtual std::string constantAsString(std::string const& name) const override;
  // receive Geant4 Geometry
  virtual G4VUserDetectorConstruction* getGeant4Geo();

private:
  /// Pointer to the interface to the DD4hep geometry
  dd4hep::Detector* m_dd4hepgeo = nullptr;
  /// Pointer to the detector construction of DDG4
  std::shared_ptr<G4VUserDetectorConstruction> m_geant4geo;

  Gaudi::Property<std::vector<std::string>> m_xmlFileNames{this, "detectors", {}, "Detector descriptions XML-files"};
  Gaudi::Property<std::map<std::string, std::string>> m_sensitive_types{
      this, "sensitiveTypes", {{"tracker", "SimpleTrackerSD"}, {"calorimeter", "SimpleCalorimeterSD"}}};
  Gaudi::Property<bool> m_buildGeant4Geo{this, "EnableGeant4Geo", true,
                                         "If True the DD4hep geometry is converted for Geant4 Simulations"};
};

#endif // K4SIMGEANT4_GEOSVC_H
