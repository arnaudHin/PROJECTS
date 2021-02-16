package fr.eseo.poo.projet.artiste.modele.formes;

import java.text.NumberFormat;
import java.util.Locale;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;

public class Ligne extends Forme{
	public static final double EPSILON = 0.1;
	
	public Ligne(Coordonnees position, double largeur, double hauteur) {
		super(position, largeur,hauteur);
	}
	
	public Ligne(double largeur, double hauteur) {
		this(new Coordonnees(), largeur, hauteur);
	}
	public Ligne(Coordonnees position) {
		this(position, Forme.LARGEUR_PAR_DEFAUT, Forme.HAUTEUR_PAR_DEFAUT);
	}
	public Ligne() {
		this(new Coordonnees(), Forme.LARGEUR_PAR_DEFAUT, Forme.HAUTEUR_PAR_DEFAUT);
	}
	
	public Coordonnees getC1() { 
		return this.getPosition(); 
		}
	public Coordonnees getC2() {
		double ord = this.getPosition().getOrdonnee()+this.getHauteur();
		/*
		if(ord < Ligne.EPSILON && ord > Ligne.EPSILON) { 
			ord = 0; 
			}
		*/
		double bs = this.getPosition().getAbscisse() + this.getLargeur();
		/*
		if(bs < Ligne.EPSILON && bs > Ligne.EPSILON) { 
			bs = 0; 
			}
		*/
		return new Coordonnees( bs , ord);
	}
	
	public void setC1(Coordonnees p1) { 
		double dX = p1.getAbscisse() - this.getC1().getAbscisse();
		double dY = p1.getOrdonnee() - this.getC1().getOrdonnee();
		this.setHauteur( this.getHauteur() - dY );
		this.setLargeur( this.getLargeur() - dX );
		this.setPosition(p1);
	}

	public void setC2(Coordonnees p2) {
		double dX = this.getC2().getAbscisse() - p2.getAbscisse();
		double dY = this.getC2().getOrdonnee() - p2.getOrdonnee();
		this.setHauteur(  this.getHauteur() - dY);
		this.setLargeur( this.getLargeur() - dX);
	}

	public double aire() { 
		return 0;
		}
	public double perimetre() { 
		return Math.sqrt(Math.pow(this.getHauteur(), 2)+ Math.pow(this.getLargeur(), 2)); 
		}
	
	public boolean contient(Coordonnees coord) {
		boolean contient = false;
		double d = this.perimetre();
		double d1 = this.getC1().distanceVers(coord);
		double d2 = this.getC2().distanceVers(coord);
		if(d1 + d2-d <= Ligne.EPSILON) { 
			contient = true; 
			}
		return contient;
	}

	public String toString() {
		double angleDeg = Math.toDegrees(this.getPosition().angleVers(this.getC2()));
		
		if(angleDeg < 0) {
			angleDeg += 360; 
			}
		
		Locale currentLocale = Locale.getDefault();
		NumberFormat nf = NumberFormat.getNumberInstance(currentLocale);
		nf.setMaximumFractionDigits(2);
		nf.setMinimumFractionDigits(1);
		
		String couleur = "";
		if(currentLocale.getLanguage().equals("fr") ) {
			couleur = "R"+String.valueOf(this.getCouleur().getRed())+",V"+String.valueOf(this.getCouleur().getGreen())+
					",B"+String.valueOf(this.getCouleur().getBlue());
		}
		else if(currentLocale.getLanguage().equals("en")) {
			couleur = "R"+String.valueOf(this.getCouleur().getRed())+",G"+String.valueOf(this.getCouleur().getGreen())+
					",B"+String.valueOf(this.getCouleur().getBlue());		
		}
		
		
		return "["+this.getClass().getSimpleName() +"]" +" c1 : ("+ nf.format(this.getC1().getAbscisse()) +" , " +
		nf.format(this.getC1().getOrdonnee()) +") c2 : (" + nf.format(this.getC2().getAbscisse()) +" , " +
		nf.format(this.getC2().getOrdonnee()) + ") longueur : "+nf.format(this.perimetre())+ " angle : "+
	nf.format(angleDeg)+"°"+" couleur = "+ couleur;
	}

}
