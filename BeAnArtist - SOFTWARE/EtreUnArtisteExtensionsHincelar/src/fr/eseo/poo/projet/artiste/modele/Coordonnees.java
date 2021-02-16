package fr.eseo.poo.projet.artiste.modele;

import java.text.NumberFormat;


import java.util.Locale;

public class Coordonnees{

	public static final double ABSCISSE_PAR_DEFAUT = 0.0;
	public static final double ORDONNEE_PAR_DEFAUT = 0.0;

	private double abscisse;
	private double ordonnee;
	
	public Coordonnees(double x, double y){
		setAbscisse(x);
		setOrdonnee(y);		
	}
	public Coordonnees(){
		this(Coordonnees.ABSCISSE_PAR_DEFAUT, Coordonnees.ORDONNEE_PAR_DEFAUT);
	}
	public void setAbscisse(double x){
		this.abscisse = x;
		}
	public void setOrdonnee(double y){
		this.ordonnee = y;
		}
	

	public double getAbscisse(){
		return this.abscisse;
		}
	public double getOrdonnee(){
		return this.ordonnee;
		}
	

	public void deplacerVers(double nlleAbscisse, double nlleOrdonnee){ 
		this.setAbscisse(nlleAbscisse); 
		this.setOrdonnee(nlleOrdonnee); 
		}
	public void deplacerDe(double deltaX, double deltaY){
		setAbscisse(this.getAbscisse()+deltaX);  
		setOrdonnee(this.getOrdonnee()+deltaY); 
		}
	
	public double distanceVers(Coordonnees coord){
		return Math.sqrt( Math.pow( coord.getAbscisse() - this.getAbscisse(),2) + 
				Math.pow(coord.getOrdonnee() - this.getOrdonnee(),2) ) ;
	}
	
	public double angleVers(Coordonnees coord){
		double deltaX = coord.getAbscisse() - this.getAbscisse();
		double deltaY = coord.getOrdonnee() - this.getOrdonnee();
		return Math.atan2(deltaY, deltaX);
	}
	
	public String toString() {
		NumberFormat nf = NumberFormat.getNumberInstance(Locale.getDefault());
		nf.setMaximumFractionDigits(2);
		nf.setMinimumFractionDigits(1);
		return "("+nf.format(this.getAbscisse())+" , "+nf.format(this.getOrdonnee())+")";
	}
}


