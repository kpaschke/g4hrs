// ********************************************************************
//
// $Id: g4hrsEMField.hh,v 1.0, 2010/12/26   HRS Exp $
// GEANT4 tag $Name: geant4-09-04 $
//
//   User Field class Setup implementation.
//
//  
#include "g4hrsEMField.hh"
#include "g4hrsTune.hh"
//////////////////////////////////////////////////////////////////////////
//
//  Constructors:

g4hrsEMField::g4hrsEMField(): mBField_Septum(0)
{

	bool pSetupHRS= true;
	if(pSetupHRS)

	fSeptumMapFile = "PREX_septumFieldMap_1320A-m2.dat";	

	mBField_Septum = new BField_Septum(fSeptumMapFile);

	bUseUniformBField=false;
//	BField3V.set(0,1.1*9.91e-4,0);
	BField3V.set(0,0,0);
}

//////////////////////////////////////////////////////////////////////////
//
//  Deconstructors:
g4hrsEMField::~g4hrsEMField()
{
	if(mBField_Septum){ delete mBField_Septum; mBField_Septum = NULL;}
}


////////////////////////////////////////////////////////////////////////////
//input Point[4] (x,y,z,t) 
//
inline void g4hrsEMField::GetFieldValue(const G4double Point[4],G4double *Bfield) const
{  
	//////////////////////////////////////////////////////////
	//get BField

	if(this->bUseUniformBField) {

                if(Point[2]/cm > 137. && Point[2]/cm < (137. + 75.) && Point[0]/cm > 0.) {
                        Bfield[0]=BField3V.x();
                        Bfield[1]=BField3V.y();
                        Bfield[2]=BField3V.z();
                } else {
                        Bfield[0]=0.;
                        Bfield[1]=0.;
                        Bfield[2]=0.;
                }

        } else {
		double pB[3],pPos[3]={Point[0]/cm,Point[1]/cm,Point[2]/cm};  //turn into cm
		for(int i=0;i<3;i++) Bfield[i]=0.0;  //reset


		//septum field read from map
		if(mBField_Septum)
		{
			for(int i=0;i<3;i++) pB[i]=0.0;  //reset
			if (! mBField_Septum->IsUniformField() ) {
				mBField_Septum->GetBField(pPos,pB);
			} else { 
				mBField_Septum->GetUniformField(pB); 
			}
			for(int i=0;i<3;i++) Bfield[i] =pB[i];
		}

	}

}
