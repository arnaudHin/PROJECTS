package fr.eseo.poo.projet.artiste.modele.formes;

import fr.eseo.poo.projet.artiste.modele.Coloriable;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import java.awt.Color;
import javax.swing.UIManager;

public abstract class Forme implements Coloriable{
	public static final double EPSILON = 0.1;
	public static final double LARGEUR_PAR_DEFAUT = 100;
	public static final double HAUTEUR_PAR_DEFAUT = 125;
	public static final Color COULEUR_PAR_DEFAUT = UIManager.getColor("Panel.foreground");
	public static final double PI = Math.PI;

	private Coordonnees position;
	private double largeur;
	private double hauteur;
	private Color couleur;

	public void setPosition(Coordonnees position){ 
		this.position = position; 
		}
	public void setLargeur(double largeur){
		this.largeur = largeur; 
		}
	public void setHauteur(double hauteur){ 
		this.hauteur = hauteur; 
		}
	public void setCouleur(Color couleur) { 
		this.couleur = couleur;	
		}
	public Coordonnees getPosition(){ 
		return this.position; 
		}
	public double getLargeur(){ 
		return this.largeur; 
		}
	public double getHauteur(){ 
		return this.hauteur; 
		}
	public Color getCouleur() {
		return this.couleur;
	}
	
	public Forme(Coordonnees position, double largeur, double hauteur){
		setPosition(position);
		setLargeur(largeur);
		setHauteur(hauteur);
		this.setCouleur(COULEUR_PAR_DEFAUT);
	}
	public Forme(double largeur, double hauteur){
		this(new Coordonnees(), largeur, hauteur);
	}
	public Forme(Coordonnees position){
		this(position, Forme.LARGEUR_PAR_DEFAUT, Forme.HAUTEUR_PAR_DEFAUT);
	}
	public Forme(){
		this(new Coordonnees(), Forme.LARGEUR_PAR_DEFAUT, Forme.HAUTEUR_PAR_DEFAUT);		
	}
	
	public Coordonnees getC1() { 
		return this.getPosition(); 
		}
	public Coordonnees getC2() {
		double ord = this.getPosition().getOrdonnee()+this.getHauteur();
		if(ord < Forme.EPSILON && ord > Forme.EPSILON) {
			ord = 0; 
			}

		double abs = this.getPosition().getAbscisse() + this.getLargeur();
		if(abs < Forme.EPSILON && abs > Forme.EPSILON) {
			abs = 0; 
			}
		return new Coordonnees( abs , ord);
	}

	public abstract double aire();
	public abstract double perimetre();
	public abstract boolean contient(Coordonnees coord);
	
	public double getCadreMinX() { 
		if(this.getLargeur() < 0) {
			return this.getPosition().getAbscisse() + this.getLargeur();
		}
		return this.getPosition().getAbscisse(); 
	}
	
	
	public double getCadreMaxX() { 
		if(this.getLargeur() > 0 ) {
			return this.getPosition().getAbscisse() + this.getLargeur();
		}
		return  this.getPosition().getAbscisse();
	}
	
	public double getCadreMinY() {
		if(this.getHauteur() < 0) {
			return this.getPosition().getOrdonnee() + this.getHauteur();
		}
		return this.getPosition().getOrdonnee(); 
	}
	
	public double getCadreMaxY() {
		if(this.getHauteur() > 0) {
			return this.getPosition().getOrdonnee() + this.getHauteur(); 
		}
		return this.getPosition().getOrdonnee();
	}	
	
	public void deplacerVers(double x, double y){
		Coordonnees coord = new Coordonnees(x, y);
		this.position.deplacerVers(coord.getAbscisse(), coord.getOrdonnee());
	}
	public void deplacerDe(double deltaX, double deltaY){
		this.position.deplacerVers(deltaX + this.getPosition().getAbscisse(), deltaY + this.getPosition().getOrdonnee());
	}
	
	public String toString() {
		return this.getClass().getSimpleName() + " pos : ("+String.valueOf(this.getPosition().getAbscisse()) +" , " +
	String.valueOf(this.getPosition().getAbscisse()) +") / dim : " + String.valueOf(this.getLargeur())+
	" x "+String.valueOf(this.getHauteur()) + " / périmètre : "+String.valueOf(this.perimetre())+
	" / aire : "+String.valueOf(this.aire());
	}
}
	
	


