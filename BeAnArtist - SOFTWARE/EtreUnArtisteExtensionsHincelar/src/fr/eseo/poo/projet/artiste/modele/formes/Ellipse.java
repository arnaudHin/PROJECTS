package fr.eseo.poo.projet.artiste.modele.formes;


import java.text.NumberFormat;

import java.util.Locale;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.Remplissable;


public class Ellipse extends Forme implements Remplissable{
	
	private boolean remplie;
	
	public Ellipse(Coordonnees position, double largeur, double hauteur){
		super(position, largeur, hauteur);
		this.setLargeur(largeur);
		this.setHauteur(hauteur);
		this.setRempli(false);
	}

	public Ellipse(double largeur, double hauteur){
		this(new Coordonnees(), largeur, hauteur);
	}
	public Ellipse(Coordonnees position){
		this(position, Forme.LARGEUR_PAR_DEFAUT, Forme.HAUTEUR_PAR_DEFAUT);
	}
	public Ellipse(){
		this(new Coordonnees(), Forme.LARGEUR_PAR_DEFAUT, Forme.HAUTEUR_PAR_DEFAUT);		
	}	
	
	public void setLargeur(double largeur){
		if (largeur < 0) { 
			throw new IllegalArgumentException(); 
		}
		super.setLargeur(largeur); 
	}
	
	public void setHauteur(double hauteur){ 
		if (hauteur < 0) { 
			throw new IllegalArgumentException(); 
		}
		super.setHauteur(hauteur); 
	}
	public double aire(){
		return 0.25*this.getHauteur()*this.getLargeur()*Forme.PI;
	}
	public double perimetre(){
		double aRayon = this.getHauteur()*0.5;
		double bRayon = this.getLargeur()*0.5;
		if(this.getHauteur() > this.getLargeur() ) {
			aRayon = this.getLargeur()*0.5;
			bRayon = this.getHauteur()*0.5;
		}

		double varh = Math.pow(((aRayon-bRayon)/(aRayon+bRayon)), 2);
		return Forme.PI*(aRayon+bRayon)*(1 + 3*varh/(10+Math.sqrt(4-3*varh)));
	}
	
	public boolean contient(Coordonnees coord) {
		boolean contient = false;
		Coordonnees center = new Coordonnees(this.getPosition().getAbscisse() + this.getLargeur()/2, 
				this.getPosition().getOrdonnee()+this.getHauteur()/2);
		double aRayon = this.getLargeur()/2;
		double bRayon = this.getHauteur()/2;
		double calc = Math.pow((coord.getAbscisse() - center.getAbscisse()), 2)/(aRayon*aRayon) +  
				Math.pow((coord.getOrdonnee() - center.getOrdonnee()), 2)/(bRayon*bRayon) ;
		if(calc <= 1 ) {
			contient = true;
		}
		return contient;
	}

	public String toString() {
		Locale currentLocale = Locale.getDefault();
		NumberFormat numberf = NumberFormat.getNumberInstance(currentLocale);
		numberf.setMaximumFractionDigits(2);
		numberf.setMinimumFractionDigits(1);
		numberf.setGroupingUsed(false);
		
		String couleur = "";

		if(currentLocale.getLanguage().equals("fr")) {
			couleur = "R"+String.valueOf(this.getCouleur().getRed())+",V"+
		String.valueOf(this.getCouleur().getGreen())+
					",B"+String.valueOf(this.getCouleur().getBlue());
		}
		else if(currentLocale.getLanguage().equals("en")) {
			couleur = "R"+String.valueOf(this.getCouleur().getRed())+",G"+
		String.valueOf(this.getCouleur().getGreen())+
					",B"+String.valueOf(this.getCouleur().getBlue());		
		}
		
		
		if(this.estRempli()) {
			return "["+this.getClass().getSimpleName() +"-Rempli] : " +"pos ("+
					numberf.format(this.getPosition().getAbscisse())+
					" , "+numberf.format(this.getPosition().getOrdonnee())+
					") dim "+numberf.format(this.getLargeur())+" x "+numberf.format(this.getHauteur())+ " périmètre : "+
					numberf.format(this.perimetre())+" aire : "+numberf.format(this.aire())+
					" couleur = "+ couleur;
		}
		else {
			return "["+this.getClass().getSimpleName() +"] : " +"pos ("+numberf.format(this.getPosition().getAbscisse())+
					" , "+ numberf.format(this.getPosition().getOrdonnee())+
				") dim "+numberf.format(this.getLargeur())+" x "+numberf.format(this.getHauteur())+ " périmètre : "+
				numberf.format(this.perimetre())+" aire : "+numberf.format(this.aire())+
				" couleur = "+ couleur;
		}
	}
	@Override
	public void setRempli(boolean modeRempli) { 
		this.remplie = modeRempli; 
		}
	@Override
	public boolean estRempli() { 
		return this.remplie; 
		}	
	
}













